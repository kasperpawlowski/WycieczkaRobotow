#include "robotsmanager.h"

RobotsManager::RobotsManager() :
    nothingRunYet(true)
{
    objects.clear();
}

RobotsManager::~RobotsManager()
{
    // assure that all the threads are finished
    killRobots();
}

bool RobotsManager::addRobot(const BaseRobot* robot)
{
    const int id         = robot->getID();
    BaseRobot *robotCopy = robot->clone();

    // overwrite protection
    if(objects.find(id) != objects.end())
    {
        return false;
    }

    // assign a new thread to the robot, assign proper connections and start the thread
    objects.insert(RTPair(id, {robotCopy, new QThread}));

    QObject::connect(objects.at(id).thread, SIGNAL(started()),
                     objects.at(id).robot, SLOT(run()));

    QObject::connect(objects.at(id).robot, SIGNAL(jobFinished()),
                     objects.at(id).thread, SLOT(quit()));

    objects.at(id).robot->moveToThread(objects.at(id).thread);
    objects.at(id).thread->start();

    nothingRunYet = false;
    return true;
}

bool RobotsManager::robotExists(const int id) const
{
    return (objects.find(id) != objects.end());
}

BaseRobot* RobotsManager::getRobot(const int id) const
{
    if(objects.find(id) == objects.end())
    {
        qCritical() << "Robots Manager: ID = " << id << " invalid, no such a robot";
    }
    return objects.at(id).robot;
}

void RobotsManager::killRobots()
{
    // finish all the threads and release the memory
    for(RTContainter::iterator it = objects.begin(); it != objects.end(); ++it)
    {
        it->second.thread->quit();
        it->second.thread->wait();
        delete it->second.thread;
        delete it->second.robot;
    }
    objects.clear();
}

bool RobotsManager::allJobsFinished()
{
    // jobs cannot be finished when nothing has run yet
    if(nothingRunYet)
    {
        return false;
    }

    // if all the threads finished, then simulation finished
    bool finished = true;
    for(RTContainter::iterator it = objects.begin(); it != objects.end(); ++it)
    {
        if(!it->second.thread->isFinished())
        {
            finished = false;
            break;
        }
    }
    return finished;
}
