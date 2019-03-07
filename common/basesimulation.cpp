#include <QEventLoop>
#include <QTimer>
#include "basesimulation.h"

BaseSimulation::BaseSimulation(const QString& interfaceUrl, QObject *parent) :
    QObject(parent)
{
    rManager = new RobotsManager;

    if(!replicaInterfaceNode_.connectToNode(interfaceUrl))
    //if(!replicaInterfaceNode_.connectToNode(QUrl("local:simulationInterfaceNode")))
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

    connect(replicaInterface_.data(), SIGNAL(situationRectDimensionsInfoFwd(const RectDimentionsType)),
            this, SLOT(situationRectDimensionsInfoHandler(const RectDimentionsType)));

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

const RectDimentionsType& BaseSimulation::getSituationRectDimensions()
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
        qCritical() << "Simulation: cannot run the simulation, initialization unsuccessful";
        emit simulationFinished();
    }
}

void BaseSimulation::situationRectDimensionsInfoHandler(const RectDimentionsType rect)
{
    dimensions_ = rect;
    emit situationRectDimensionsReady();
}

void BaseSimulation::checkIfFinished()
{
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

    qInfo() << "Simulation: simulation started";
    emit clearReq();
    runSimulation();
}

void BaseSimulation::stop()
{
    rManager->killRobots();
}
