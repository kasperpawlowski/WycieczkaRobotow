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
     * \brief addRobot adds the robot to the inner container, creates
     *        a new thread for the robot and runs it. When the thread
     *        starts, the robot begins to execute its role
     * \param[in] robot a pointer to the robot that will be
     * \return
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
     * \param[in] id an identifier of the robot being managed
     * \return pointer to the desired robot
     */
    BaseRobot* getRobot(const int id) const;

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
     * \brief The RobotThread struct groups robot and its thread
     */
    struct RobotThread
    {
        BaseRobot *robot;
        QThread   *thread;
    };

    typedef std::map<int, RobotThread>  RTContainter;
    typedef std::pair<int, RobotThread> RTPair;

    /*!
     * \brief objects robot-thread pairs managed by the manager
     */
    RTContainter objects;

    /*!
     * \brief nothingRunYet marks whether any simulation has run so far
     */
    bool nothingRunYet;
};

#endif // ROBOTSMANAGER_H
