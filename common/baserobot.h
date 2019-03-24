#ifndef BASEROBOT_H
#define BASEROBOT_H

#include <QObject>
#include "commoninterfaceuser.h"

/*!
 * \brief The BaseRobot class is an abstract robot class that has an access to
 *        the GUI in order to display a pixmap that represents it on the screen
 *
 * BaseRobot derives from CommonInterfaceUser to have an access to the interface
 * connecting to the SituationScene. Provides basic methods to display itself,
 * delete itself from the screen or update its position.
 */
class BaseRobot : public CommonInterfaceUser
{
    Q_OBJECT
public:
    enum SIMULATION_SPEED {FAST = 1, MEDIUM = 10, SLOW = 50};

    /*!
     * \brief BaseRobot creates a new BaseRobot described by the provided identifier
     * \param[in] id an identifier that will describe the robot
     * \param[in] rep a pointer to the Qt Remote Object inteface replica
     */
    BaseRobot(const int id, const BSIReplicaSP rep);

    /*!
     * \brief BaseRobot a copy constructor
     */
    BaseRobot(const BaseRobot& robot);

    /*!
     * \brief ~BaseRobot destructs the BaseRobot
     */
    virtual ~BaseRobot();

    /*!
     * \brief clone polymorphic copy constructor, must be defined in every
     *        class that derives from BaseRobot
     * \return pointer to the newly created copy of the object
     */
    virtual BaseRobot* clone() const = 0;

    /*!
     * \brief setRobotSimulationSpeed sets speed of the robot simulation
     *        (for the most realistic results, all the robots should have
     *         the same simulation speed)
     * \param[in] speed requested simulation speed
     */
    void setRobotSimulationSpeed(SIMULATION_SPEED speed) {simSpeed_ = speed;}

    /*!
     * \brief getRobotSimulationSpeed returns particular robot's simulation speed
     * \return simulation speed
     */
    SIMULATION_SPEED getRobotSimulationSpeed() const {return simSpeed_;}

    /*!
     * \brief getLoopCount returns number of repetitions of the robot's loop
     *        (in fact, it is number of simulationPeriodicControl() calls)
     * \return number of repetitions
     */
    unsigned int getLoopCount() const {return loopCounter_;}
signals:
    /*!
     * \brief jobFinished emitted when the robot finishes its role
     */
    void jobFinished();

public slots:
    /*!
     * \brief run callable entry point of the robot simulation
     */
    virtual void run();

protected:
    /*!
     * \brief simulationPeriodicControl processes events, waits for the time corresponding
     *        to the simulation speed, increments the loop counter
     *
     * This method should be called in runRobot in every repetition of its inner loop.
     * May be overloaded but the overloading method should call the original method
     */
    virtual void simulationPeriodicControl();

private:
    BaseRobot() = delete;

    /*!
     * \brief runRobot shall be defined by classes that derive from BaseRobot
     *
     * This is the real entry point of the simulation for each robot. The robot
     * simulation logic shall be defined in this method. simulationPeriodicControl()
     * method shall be called periodically in a loop so the robot keeps being responsive
     * and the simulation runs at desired pace. It is assumed than when the robot returns
     * from this method its job is finished.
     */
    virtual void runRobot() = 0;

    SIMULATION_SPEED simSpeed_;
    unsigned int     loopCounter_;
};

#endif // BASEROBOT_H
