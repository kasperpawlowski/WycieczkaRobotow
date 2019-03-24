#ifndef TWOWHEELSROBOT_H
#define TWOWHEELSROBOT_H

#include "baserobot.h"
#include "basicsensor.h"
#include "radiodevice.h"

/*!
 * \brief The TwoWheelsRobot class is a simple differential drive robot class that
 *        derives from BaseRobot
 *
 * It contains a GPS-like sensor that lets the robot know its current coordinates.
 * It contains a magnetometer that lets the robot know its current orientation angle.
 * It contains a radio device that can transmit Position data to other robots (mode
 * used by the leader) or receive Position data from other robots (mode used by
 * the followers).
 */
class TwoWheelsRobot : public BaseRobot
{
    Q_OBJECT
public:
    /*!
     * \brief TwoWheelsRobot constructs a new TwoWheelsRobot of provided identifier
     * \param[in] id new robot's identifier
     * \param[in] rep a pointer to the Qt Remote Object inteface replica
     */
    TwoWheelsRobot(const int id, const BSIReplicaSP rep);

    /*!
     * \brief TwoWheelsRobot copy contructor
     * \param[in] robot TwoWheelsRobot to be copied
     */
    TwoWheelsRobot(const TwoWheelsRobot& robot);
    ~TwoWheelsRobot();

    /*!
     * \brief setInitialPosition sets initial position of the robot
     * \param[in] pos initial position
     * \return true on success, false otherwise
     */
    bool setInitialPosition(Position pos);

    /*!
     * \brief setWheelDiameter sets both wheels diameter
     * \param[in] d diameter [m]
     */
    void setWheelDiameter(const double d) {wheelDiameter_ = d;}

    /*!
     * \brief setWheelBaseLength sets distance between the wheels
     * \param[in] l distance between the wheels [m]
     */
    void setWheelBaseLength(const double l) {wheelBaseLength_ = l;}

    /*!
     * \brief setWheelMaxSpeed sets maximum linear speed of the robot
     * \param[in] ms max speed [m/s]
     */
    void setWheelMaxSpeed(const double ms) {wheelMaxSpeed_ = ms;}

    /*!
     * \brief getWheelDiameter returns robot's wheels diameter [m]
     * \return
     */
    double getWheelDiameter() const {return wheelDiameter_;}

    /*!
     * \brief getWheelBaseLength returns distance between the wheels [m]
     * \return
     */
    double getWheelBaseLength() const {return wheelBaseLength_;}

    /*!
     * \brief getWheelMaxSpeed returns maximum speed of the robot [m/s]
     * \return
     */
    double getWheelMaxSpeed() const {return wheelMaxSpeed_;}

    /*!
     * \brief getRadio returns a pointer to the robot's radio device
     * \return
     */
    RadioDevice* getRadio() const {return radio;}

protected:
    /*!
     * \brief getHeadingToNextPoint computes heading from current to desired position
     * \return computed heading
     */
    double getHeadingToNextPoint();

    /*!
     * \brief The WheelsSpeed struct describes commanded angular speeds of both wheels
     */
    struct WheelsSpeed
    {
        double leftWheel;
        double rightWheel;
    };

    /// indicates whether the robot finished its role
    bool jobFinished;

    /// simulation time step [s]
    const double dt;

    /// commanded angular speeds of both wheels [rad/s]
    WheelsSpeed commandedSpeeds;

    /// position from the previous step of the simulation
    Position previousPos;

    /// position the robot is travelling to
    Position desiredPos;

    /// current position of the robot
    Position currentPos;

    /// measures current coordinates
    BasicSensor<Point, Point>   *GPS;

    /// measures current orientation angle
    BasicSensor<double, double> *magnetometer;

    /// transmits/receives Position data
    RadioDevice *radio;

    /// holds accumulated distance travelled
    double distance;

private:
    TwoWheelsRobot() = delete;

    /*!
     * \brief runRobot calls simulationPeriodicControl(), runKinematicsStep(),
     *        useOnboardEquipment() and determineNewCommands() untill the role
     *        for this robot is finished
     *
     * This method may be overloaded to perform more sophisticated actions.
     */
    void runRobot();

    /*!
     * \brief runKinematicsStep performs one movement step based on commanded
     *        speed of the wheels
     *
     * This method may be overloaded to perform more sophisticated actions.
     */
    virtual void runKinematicsStep();

    /*!
     * \brief useOnboardEquipment shall be defined by classes that derive from
     *        TwoWheelsRobot
     *
     * This method shall be responsible for appropriate use of the robot's onboard
     * equipment.
     */
    virtual void useOnboardEquipment() = 0;

    /*!
     * \brief determineNewCommands computes commanded speed of the wheels for the
     *        next movement step
     *
     * This method may be overloaded to perform more sophisticated actions.
     */
    virtual void determineNewCommands();

    double wheelDiameter_;
    double wheelBaseLength_;
    double wheelMaxSpeed_;
};

#endif // TWOWHEELSROBOT_H
