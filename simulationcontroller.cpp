#include <QTimer>
#include "simulationcontroller.h"

SimulationController::SimulationController(QObject *parent) :
    QObject(parent)
{

}

SimulationController::~SimulationController()
{

}

void SimulationController::startSimulation(const SituationScene *situation)
{
    // create interface object and host it to the other process
    interface_     = new SimulationInterface(situation);
    interfaceNode_ = new QRemoteObjectHost(interfaceUrl_);
    interfaceNode_->enableRemoting(interface_);

    // run simulation
    QStringList arguments;
    simulation_ = new QProcess;

    arguments << interfaceUrl_;
    simulation_->start(simulationFilePath_, arguments);

    if(!simulation_->waitForStarted())
    {
        qCritical() << "Simulation Controller: unable to start the simulation";
        QTimer::singleShot(0, situation, SLOT(simulationFinished()));
        return;
    }
}

void SimulationController::stopSimulation()
{
    if(simulation_)
    {
        simulation_->kill();
        simulation_->waitForFinished();
        delete simulation_;
        delete interfaceNode_;
        delete interface_;
        simulation_ = nullptr;
    }
}
