#include <QCoreApplication>
#include <QThread>
#include "baserobot.h"

BaseRobot::BaseRobot(const int id, const BSIReplicaSP rep) :
    CommonInterfaceUser(id, rep), simSpeed_(MEDIUM), loopCounter_(0)
{

}

BaseRobot::BaseRobot(const BaseRobot& robot) :
    CommonInterfaceUser(robot), simSpeed_(robot.simSpeed_), loopCounter_(robot.loopCounter_)
{

}

BaseRobot::~BaseRobot()
{

}

void BaseRobot::run()
{
    if(!addPixmap())
    {
        qCritical() << "Base Robot: cannot add robot (ID =" << getID() << ") to GUI";
        emit jobFinished();
        return;
    }

    // run the robots's main control loop. if returns from runRobot(), the job is finished
    runRobot();
    emit jobFinished();
}

void BaseRobot::simulationPeriodicControl()
{
    QCoreApplication::processEvents();
    QThread::msleep(simSpeed_);
    loopCounter_++;
}
