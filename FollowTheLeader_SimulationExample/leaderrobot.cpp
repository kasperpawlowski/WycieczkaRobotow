#include "leaderrobot.h"

LeaderRobot::LeaderRobot(const int id, const BSIReplicaSP rep) :
    TwoWheelsRobot(id, rep)
{
    path_ = nullptr;
    radio = new RadioDevice(RadioDevice::TRANSMITTER);
}

LeaderRobot::LeaderRobot(const LeaderRobot& robot) :
    TwoWheelsRobot(robot)
{
    path_ = robot.path_;
    radio = new RadioDevice(*robot.radio);
}

LeaderRobot::~LeaderRobot()
{
    delete radio;
}

BaseRobot* LeaderRobot::clone() const
{
    return new LeaderRobot(*this);
}

void LeaderRobot::setPath(std::list<Point> *path)
{
    path_ = path;
}

void LeaderRobot::useOnboardEquipment()
{
    // save previous position
    previousPos = currentPos;

    // determine self position
    currentPos.setXY(GPS->get());
    currentPos.setA(magnetometer->get());

    // accumulate travelled distance
    distance += previousPos.distanceTo(currentPos);

    // transmit leader current position to the followers
    radio->TransmitData(currentPos);

    // check if we are close to the desired position
    if(currentPos.distanceTo(desiredPos) < getWheelBaseLength()/2.0)
    {
        // obtain the next desired position from the container
        if(path_->size() > 0)
        {
            desiredPos.setXY(path_->front());
            path_->pop_front();
        }
        // if travelled through the whole path, simulation is finished for the leader
        else
        {
            qInfo() << "Leader Robot ID " << getID() << ": travelled " << distance << " meters in " << getLoopCount()*dt << "seconds";
            qInfo() << "Leader Robot ID " << getID() << ": average speed = " << distance/(getLoopCount()*dt);
            emit LeaderAtGoal();
            jobFinished = true;
        }
    }

    // update the desired heading in every step (as the robot is moving bearing to the
    // desired point changes)
    desiredPos.setA(getHeadingToNextPoint());
}
