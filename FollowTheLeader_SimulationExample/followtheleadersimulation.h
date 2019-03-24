#ifndef FOLLOWTHELEADERSIMULATION_H
#define FOLLOWTHELEADERSIMULATION_H

#include <QThread>
#include "basesimulation.h"

/*!
 * \brief The FollowTheLeaderSimulation class is a class that constructs a leader
 *        robot and its followers so control of robot formation using leader
 *        following method can be performed
 *
 * The class prepares the path data that will be travelled by the leader by reading
 * it from previously created file. It also prepares the formation data by reading
 * if from previously creaded file and chooses a leader. It creates and initializes
 * all the robots and adds them to the RobotsManager. Finally, it runs simulation.
 */
class FollowTheLeaderSimulation : public BaseSimulation
{
    Q_OBJECT
public:
    /*!
     * \brief FollowTheLeaderSimulation constructs a new FollowTheLeaderSimulation
     * \param[in] interfaceUrl URL of the Qt Remote Object simulation interface
     * \param[in] parent a parent object
     */
    FollowTheLeaderSimulation(const QString& interfaceUrl, QObject *parent = nullptr);

    /*!
     * \brief ~FollowTheLeaderSimulation destructs the FollowTheLeaderSimulation
     */
    ~FollowTheLeaderSimulation() {}

private slots:
    void runSimulation();

private:
    FollowTheLeaderSimulation() = delete;
    void chooseALeader();
    void formationToLeaderCoordinates();
    void createAndFeedTheLeader();
    void createAndFeedFollowers();
};

#endif // FOLLOWTHELEADERSIMULATION_H
