#include <QEventLoop>
#include <QTimer>
#include "basesimulation.h"
#include "filesgenerator.h"

BaseSimulation::BaseSimulation(const QString& interfaceUrl, QObject *parent) :
    QObject(parent)
{
    scaleFactor = 1.0;
    rManager    = new RobotsManager;
    worldPath.clear();
    worldFormation.clear();

    if(!replicaInterfaceNode_.connectToNode(interfaceUrl))
    {
        qInfo() << "Simulation: cannot connect to the Qt Remote Object Node";
        return;
    }

    replicaInterface_.reset(replicaInterfaceNode_.acquire<BaseSimulationInterfaceReplica>());

    if(replicaInterface_.isNull())
    {
        qInfo() << "Simulation: cannot acquire BaseSimulationInterfaceReplica object";
        return;
    }

    // connect to the interface replica
    connect(this, SIGNAL(clearReq()),
            replicaInterface_.data(), SLOT(clearReqReemit()));

    connect(this, SIGNAL(situationRectDimensionsReq()),
            replicaInterface_.data(), SLOT(situationRectDimensionsReqReemit()));

    connect(this, SIGNAL(simulationFinished()),
            replicaInterface_.data(), SLOT(simulationFinishedReemit()));

    connect(replicaInterface_.data(), SIGNAL(cannotAddObjectFwd(const int)),
            this, SLOT(cannotAddObjectHandler(const int)));

    connect(replicaInterface_.data(), SIGNAL(cannotDeleteObjectFwd(const int)),
            this, SLOT(cannotDeleteObjectHandler(const int)));

    connect(replicaInterface_.data(), SIGNAL(cannotUpdateObjectPositionFwd(const int)),
            this, SLOT(cannotUpdateObjectPositionHandler(const int)));

    connect(replicaInterface_.data(), SIGNAL(situationRectDimensionsInfoFwd(const RectDimensionsType)),
            this, SLOT(situationRectDimensionsInfoHandler(const RectDimensionsType)));

    connect(replicaInterface_.data(), SIGNAL(initialized()),
            this, SLOT(interfaceReadyHandler()));

    connect(&auxiliaryTimer_, SIGNAL(timeout()),
            this, SLOT(interfaceReadyHandler()));

    // if the source not ready in 5 seconds, stop the simulation
    auxiliaryTimer_.setSingleShot(true);
    auxiliaryTimer_.start(5000);
}

BaseSimulation::~BaseSimulation()
{
    delete rManager;
}

const RectDimensionsType& BaseSimulation::getSituationRectDimensions()
{
    emit situationRectDimensionsReq();

    // wait for dimensions to be delivered (max 1 second)
    QEventLoop loop;
    QTimer     timer;

    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(this, SIGNAL(situationRectDimensionsReady()), &loop, SLOT(quit()));
    timer.start(1000);
    loop.exec();

    if(!timer.isActive())
    {
        qInfo() << "Simulation: timeout while waiting for situation rectangle dimensions";
    }

    return dimensions_;
}

bool BaseSimulation::readAndMakeWorldPath(const QString filePath)
{
    // let's assume that 20 pixels is 1 meter
    const double X_PIXELS_IS_1_METER = 20.0;
    std::list<QPoint> points = FilesGenerator<std::list>::readFromFile(filePath);

    worldPath.clear();
    for(auto it = points.begin(); it != points.end(); ++it)
    {
        worldPath.push_back({it->x()/X_PIXELS_IS_1_METER, it->y()/X_PIXELS_IS_1_METER});
    }

    if(worldPath.size() > 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BaseSimulation::readAndMakeWorldFormation(const QString filePath)
{
    // let's assume that minimal spacing between robots is 1 meter
    const double MIN_SPACING_IS_X_METERS = 1.0;
    std::vector<QPoint> points = FilesGenerator<std::vector>::readFromFile(filePath);

    worldFormation.clear();
    for(auto it = points.begin(); it != points.end(); ++it)
    {
        worldFormation.push_back({it->x()*MIN_SPACING_IS_X_METERS, it->y()*MIN_SPACING_IS_X_METERS});
    }

    if(worldFormation.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BaseSimulation::computeScaleFactor()
{
    dimensions_ = getSituationRectDimensions();
    std::pair<double, double> max_XY = {0.0, 0.0};

    if(worldPath.size() < 2)
    {
        qCritical() << "Base Simulation: cannot compute the scale factor";
        scaleFactor = 1.0;
        return false;
    }

    // find max X and max Y coordinates
    for(auto it = worldPath.begin(); it != worldPath.end(); ++it)
    {
        if(it->getX() > max_XY.first)
        {
            max_XY.first = it->getX();
        }

        if(it->getY() > max_XY.second)
        {
            max_XY.second = it->getY();
        }
    }

    // compute the scale factor
    scaleFactor = 0.9*std::min(dimensions_.width/max_XY.first, dimensions_.height/max_XY.second);
    return true;
}

void BaseSimulation::interfaceReadyHandler()
{
    if(auxiliaryTimer_.isActive())
    {
        // stop the timer and disconnect so it can be used for different purposes
        auxiliaryTimer_.stop();
        disconnect(&auxiliaryTimer_, SIGNAL(timeout()),
                    this, SLOT(interfaceReadyHandler()));

        emit interfaceReady();
    }
    else
    {
        qCritical() << "Simulation: cannot run the simulation, initialization unsuccessful (timeout)";
        emit simulationFinished();
    }
}

void BaseSimulation::situationRectDimensionsInfoHandler(const RectDimensionsType rect)
{
    dimensions_ = rect;
    emit situationRectDimensionsReady();
}

void BaseSimulation::checkIfFinished()
{
    // check if all robots finished their job or whether the interface replica is broken
    if(rManager->allJobsFinished() || !replicaInterface_.data()->isReplicaValid())
    {
        qInfo() << "Simulation: simulation finished";
        emit simulationFinished();
    }
}

void BaseSimulation::cannotAddObjectHandler(const int id)
{
    qInfo() << "Simulation: cannot add object, ID = " << id;
}

void BaseSimulation::cannotDeleteObjectHandler(const int id)
{
    qInfo() << "Simulation: cannot delete object, ID = " << id;
}

void BaseSimulation::cannotUpdateObjectPositionHandler(const int id)
{
    qInfo() << "Simulation: cannot update object position, ID = " << id;
}

void BaseSimulation::run()
{
    // set up the timer to periodically check whether the simulation is finished
    auxiliaryTimer_.setSingleShot(false);
    connect(&auxiliaryTimer_, SIGNAL(timeout()), this, SLOT(checkIfFinished()));
    auxiliaryTimer_.start(1000);

    // run the simulation and start all the robots' threads
    emit clearReq();
    runSimulation();
    rManager->startRobots();
    qInfo() << "Simulation: simulation started";
}

void BaseSimulation::stop()
{
    rManager->killRobots();
}
