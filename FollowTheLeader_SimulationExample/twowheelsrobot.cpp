#include "twowheelsrobot.h"

TwoWheelsRobot::TwoWheelsRobot(const int id, const BSIReplicaSP rep) :
    BaseRobot(id, rep), dt(0.02)
{
    jobFinished     = false;
    commandedSpeeds = {0.0, 0.0};
    previousPos     = {0, 0, 0.0};
    desiredPos      = {0, 0, 0.0};
    currentPos      = {0, 0, 0.0};
    GPS             = new BasicSensor<Point, Point>();
    magnetometer    = new BasicSensor<double, double>();
}

TwoWheelsRobot::TwoWheelsRobot(const TwoWheelsRobot& robot) :
    BaseRobot(robot), dt(robot.dt)
{
    jobFinished      = robot.jobFinished;
    commandedSpeeds  = robot.commandedSpeeds;
    previousPos      = robot.previousPos;
    desiredPos       = robot.desiredPos;
    currentPos       = robot.currentPos;
    GPS              = new BasicSensor<Point, Point>(*robot.GPS);
    magnetometer     = new BasicSensor<double, double>(*robot.magnetometer);
    wheelDiameter_   = robot.wheelDiameter_;
    wheelBaseLength_ = robot.wheelBaseLength_;
    wheelMaxSpeed_   = robot.wheelMaxSpeed_;
}

TwoWheelsRobot::~TwoWheelsRobot()
{
    delete GPS;
    delete magnetometer;
}

bool TwoWheelsRobot::setInitialPosition(Position pos)
{
    // the position may be set from the outside only before sending it to GUI
    if(isSentToGUI())
    {
        return false;
    }

    previousPos = desiredPos = currentPos = pos;
    updatePixmapPosition(pos * getScaleFactor());
    return true;
}

double TwoWheelsRobot::getHeadingToNextPoint()
{
    return atan2((desiredPos-currentPos).getY(), (desiredPos-currentPos).getX())*180.0/M_PI;
}

void TwoWheelsRobot::runRobot()
{
    while(!jobFinished)
    {
        simulationPeriodicControl();
        runKinematicsStep();
        useOnboardEquipment();
        determineNewCommands();
    }
}

void TwoWheelsRobot::runKinematicsStep()
{
    // for each wheel calculate the distance travelled in one step
    const double dLeftWheel  = commandedSpeeds.leftWheel  * wheelDiameter_ * 0.5 * dt;
    const double dRightWheel = commandedSpeeds.rightWheel * wheelDiameter_ * 0.5 * dt;
    const double dCenter     = (dLeftWheel + dRightWheel) / 2.0;

    // calculate the travelled vector
    Position delta;
    delta.setX(dCenter * cos(currentPos.getA() * M_PI/180.0));
    delta.setY(dCenter * sin(currentPos.getA() * M_PI/180.0));
    delta.setA((dRightWheel - dLeftWheel) / wheelBaseLength_);

    // calculate new real position
    const Position localCurrentPos = currentPos + delta;

    // set sensors' inputs
    GPS->set(localCurrentPos);
    magnetometer->set(localCurrentPos.getA());

    // update pixmap position
    updatePixmapPosition(localCurrentPos * getScaleFactor());
}

void TwoWheelsRobot::determineNewCommands()
{
    const double hdg_diff = desiredPos.getA() - currentPos.getA();

    // PID coefficients
    const double  Kp      = 100.0;
    const double  Ki      = 0.0;
    const double  Kd      = 0.0;
    static double prev_eP = 0.0;
    static double prev_eI = 0.0;
    double        curr_eP = atan2(sin(hdg_diff*M_PI/180.0), cos(hdg_diff*M_PI/180.0));
    double        curr_eI = prev_eI + curr_eP*dt;
    double        curr_eD = (curr_eP - prev_eP)/dt;

    prev_eP = curr_eP;
    prev_eI = curr_eI;

    // calculate appropriate heading change rate (in radians)
    double omegaHeading = curr_eP*Kp + curr_eI*Ki + curr_eD*Kd;

    // calculate appropriate wheel velocity. when omegaHeading increases,
    // the velWheel drops
    double velWheel = wheelMaxSpeed_ / pow(abs(omegaHeading) + 1.0, 0.2);

    // calculate left and right wheel velocities
    if(currentPos.distanceTo(desiredPos) >= getWheelBaseLength()/3.0)
    {
        commandedSpeeds.leftWheel  = ((2.0 * velWheel) - (omegaHeading * wheelBaseLength_)) / wheelDiameter_;
        commandedSpeeds.rightWheel = ((2.0 * velWheel) + (omegaHeading * wheelBaseLength_)) / wheelDiameter_;
    }
    else if(currentPos.headingAbsDiff(desiredPos) > 0.1)
    {
        commandedSpeeds.leftWheel  = -(omegaHeading * wheelBaseLength_) / wheelDiameter_;
        commandedSpeeds.rightWheel =  (omegaHeading * wheelBaseLength_) / wheelDiameter_;
    }
    else
    {
        // we're in the right place, don't have to move anywhere
        commandedSpeeds = {0.0, 0.0};
    }
}
