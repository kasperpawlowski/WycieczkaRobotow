#ifndef ROBOTSMANAGER_H
#define ROBOTSMANAGER_H

#include <QThread>
#include "baserobot.h"

/*!
 * \brief The RobotsManager class manages all robots population by creating
 *        a new thread for each robot and managing it
 */
class RobotsManager
{
public:
    /*!
     * \brief RobotsManager creates a new RobotsManager
     */
    RobotsManager();

    /*!
     * \brief ~RobotsManager destructs the RobotsManager
     */
    virtual ~RobotsManager();

    /*!
     * \brief addRobot adds the robot to the inner container and creates
     *        a new thread for it
     * \param[in] robot a pointer to the robot that will be managed
     * \return true on success, false otherwise
     *
     * Important information: keep in mind that adding the robot to the manager
     * disconnects all the connections of the BaseRobot derived classes and their
     * components. It means that only the connections made by the BaseRobot class are
     * preserved, while all the other must be made again. Therefore it is advised
     * to make all the necessary connections for the derived class after adding the
     * robots to the manager. It can be done with use of getRobot() method to get
     * the pointer to the robot object.
     */
    bool addRobot(const BaseRobot* robot);

    /*!
     * \brief robotExists checks whether a robot described by provided
     *        identifier is managed by the manager
     * \param[in] id an identifier of the robot
     * \return true when the manager manages the robot of provided identifier,
     *         false otherwise
     */
    bool robotExists(const int id) const;

    /*!
     * \brief getRobot returns the robot managed by the manager. The user
     *        must be sure that the robot is currently being managed
     *        (i.e proper identifier must be given)
     * \param[in] id an identifier of the robot being managed
     * \return pointer to the desired robot
     */
    BaseRobot* getRobot(const int id) const;

    /*!
     * \brief startRobots starts all the previously created robots' threads.
     *        When the threads are started, all the robots begin to execute
     *        their roles
     */
    void startRobots();

    /*!
     * \brief killRobots kills all the robots' related threads and clears
     *        the manager
     */
    void killRobots();

    /*!
     * \brief allJobsFinished checks whether all the robots' related threds have
     *        finished
     * \return true when all the threads have finished, false otherwise
     */
    bool allJobsFinished();

protected:
    /*!
     * \brief The RobotThread struct groups robot and its thread for ease of maintenance
     */
    struct RobotThread
    {
        BaseRobot *robot;
        QThread   *thread;
    };

    typedef std::map<int, RobotThread>  RTContainter;
    typedef std::pair<int, RobotThread> RTPair;

    /// objects robot-thread pairs managed by the manager
    RTContainter objects;

    /// marks whether any simulation has run so far
    bool nothingRunYet;
};

#endif // ROBOTSMANAGER_H
