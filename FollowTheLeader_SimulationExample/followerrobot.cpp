#include "followerrobot.h"

FollowerRobot::FollowerRobot(const int id, const BSIReplicaSP rep):
    TwoWheelsRobot(id, rep)
{
    leaderAtGoal_      = false;
    fromRadioPos_      = {0, 0, 0.0};
    leaderRelativePos_ = {0, 0, 0.0};
    radio              = new RadioDevice(RadioDevice::RECEIVER);
}

FollowerRobot::FollowerRobot(const FollowerRobot& robot) :
    TwoWheelsRobot(robot)
{
    leaderAtGoal_      = robot.leaderAtGoal_;
    fromRadioPos_      = robot.fromRadioPos_;
    leaderRelativePos_ = robot.leaderRelativePos_;
    radio              = new RadioDevice(*robot.radio);
}

FollowerRobot::~FollowerRobot()
{
    delete radio;
}

BaseRobot* FollowerRobot::clone() const
{
    return new FollowerRobot(*this);
}

Position FollowerRobot::getLeaderRelativeRotatedPos(const double rot_angle_deg) const
{
    const double rot_angle_rad = rot_angle_deg*M_PI/180.0;
    return Position(leaderRelativePos_.getX()*cos(rot_angle_rad) - leaderRelativePos_.getY()*sin(rot_angle_rad),
                    leaderRelativePos_.getX()*sin(rot_angle_rad) + leaderRelativePos_.getY()*cos(rot_angle_rad),
                    leaderRelativePos_.getA());
}

void FollowerRobot::LeaderAtGoalHandler()
{
    leaderAtGoal_ = true;
}

void FollowerRobot::useOnboardEquipment()
{
    static bool nothing_received_yet = true;

    // save previous position
    previousPos = currentPos;

    // determine self position
    currentPos.setXY(GPS->get());
    currentPos.setA(magnetometer->get());

    // accumulate travelled distance
    distance += previousPos.distanceTo(currentPos);

    // determine the leader position
    if(radio->newDataReceived())
    {
        fromRadioPos_ = radio->ReceiveData();
        nothing_received_yet = false;
    }
    // if nothing received from the leader yet, set the fromRadioPos_ to currentPos
    // so the robot does not move
    else if(nothing_received_yet)
    {
        fromRadioPos_ = currentPos;
    }

    // precision controller
    if(currentPos.distanceTo(desiredPos) < getWheelBaseLength()/2.0)
    {
        // calculate new desired position
        desiredPos = fromRadioPos_ + getLeaderRelativeRotatedPos(fromRadioPos_.getA());

        // check if we are close to the desired position and if the leader at goal
        if((currentPos.headingAbsDiff(desiredPos) < 1.0) &&
            leaderAtGoal_)
        {
            qInfo() << "Follower Robot ID " << getID() << ": travelled " << distance << " meters in " << getLoopCount()*dt << "seconds";
            qInfo() << "Follower Robot ID " << getID() << ": average speed = " << distance/(getLoopCount()*dt);
            jobFinished = true;
        }
    }
    // point to point controller
    else
    {
        // calculate new desired position
        desiredPos = fromRadioPos_ + getLeaderRelativeRotatedPos(fromRadioPos_.getA());

        // if not at desired position, update the desired orientation angle in every step
        // (as the leader robot is moving bearing to the desired point changes)
        desiredPos.setA(getHeadingToNextPoint());
    }
}
