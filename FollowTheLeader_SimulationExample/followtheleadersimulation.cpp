#include "QThread"
#include "followtheleadersimulation.h"
#include "leaderrobot.h"
#include "followerrobot.h"

FollowTheLeaderSimulation::FollowTheLeaderSimulation(const QString& interfaceUrl, QObject *parent) :
    BaseSimulation(interfaceUrl, parent)
{

}

void FollowTheLeaderSimulation::runSimulation()
{
    if(!readAndMakeWorldPath(".\\data\\PathData.txt"))
    {
        qCritical() << "Follow The Leader Simulation: cannot read the path";
        return;
    }

    if(!readAndMakeWorldFormation(".\\data\\FormationData.txt"))
    {
        qCritical() << "Follow The Leader Simulation: cannot read the formation";
        return;
    }

    if(!computeScaleFactor())
    {
        qCritical() << "Follow The Leader Simulation: cannot compute scale factor";
    }

    createAndFeedTheLeader();
    createAndFeedFollowers();

    // connect leader's signals to the followers' slots
    RadioDevice *leader_radio = dynamic_cast<LeaderRobot*>(rManager->getRobot(0))->getRadio();
    for (int i=1; i < int(worldFormation.size()); ++i)
    {
        RadioDevice *follower_radio = dynamic_cast<FollowerRobot*>(rManager->getRobot(i))->getRadio();

        connect(rManager->getRobot(0), SIGNAL(LeaderAtGoal()),
                rManager->getRobot(i), SLOT(LeaderAtGoalHandler()));

        connect(leader_radio,   SIGNAL(Transmit(Position)),
                follower_radio, SLOT(Receive(Position)));
    }

    // pop the first point of the path, all the robots are already there
    worldPath.pop_front();
}

void FollowTheLeaderSimulation::chooseALeader()
{
    Point leader_coords;

    // for example choose the most right robot
    if(worldFormation.size() > 0)
    {
        leader_coords = worldFormation.front();

        for(auto it = worldFormation.begin(); it != worldFormation.end(); ++it)
        {
            if(it->getX() > leader_coords.getX())
            {
                leader_coords = *it;
            }
        }
    }

    for(auto it = worldFormation.begin(); it != worldFormation.end(); ++it)
    {
        *it = *it - leader_coords;
    }
}

void FollowTheLeaderSimulation::createAndFeedTheLeader()
{
    LeaderRobot leader(0, getReplicaInterface());
    chooseALeader();
    leader.setPath(&worldPath);

    leader.setWheelDiameter(0.1);
    leader.setWheelBaseLength(0.5);
    leader.setWheelMaxSpeed(1.0);

    leader.setScaleFactor(scaleFactor);
    leader.setPixmapFile(".\\data\\pixmaps\\leader.png");

    leader.setPixmapSize({int(leader.getWheelBaseLength() * scaleFactor),
                          int(leader.getWheelBaseLength() * scaleFactor)});

    leader.setInitialPosition(Position(worldPath.front(), 0.0));

    rManager->addRobot(&leader);
}

void FollowTheLeaderSimulation::createAndFeedFollowers()
{
    int id = 1;
    for (auto it = worldFormation.begin(); it != worldFormation.end(); ++it)
    {
        // check if leader
        if((it->getX() == 0.0) && (it->getY() == 0.0))
        {
            continue;
        }

        FollowerRobot follower(id, getReplicaInterface());
        follower.setLeaderRelativePos(Position(*it, 0.0));

        follower.setWheelDiameter(0.1);
        follower.setWheelBaseLength(0.5);
        follower.setWheelMaxSpeed(1.5);

        follower.setScaleFactor(scaleFactor);
        follower.setPixmapFile(".\\data\\pixmaps\\follower.png");

        follower.setPixmapSize({int(follower.getWheelBaseLength() * scaleFactor),
                                int(follower.getWheelBaseLength() * scaleFactor)});

        // let's assume that the formation coordinates from the file, describe
        // the formation in the moment the leaders orientation angle is 0.
        // therefore if current leaders initial orientation angle is not 0,
        // then whole formation should be initially rotated
        follower.setInitialPosition(Position(worldPath.front(), 0.0) +          // <-- current leaders position and orientation
                                    follower.getLeaderRelativeRotatedPos(0.0)); // <-- current leaders orientation

        rManager->addRobot(&follower);
        id++;
    }
}
