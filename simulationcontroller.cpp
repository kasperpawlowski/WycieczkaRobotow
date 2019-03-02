#include <QDebug>
#include <QProcess>
#include "simulationcontroller.h"
#include "simulationinterface.h"

SimulationController::SimulationController(QObject *parent) :
    QThread(parent) {}

void SimulationController::startSimulation(const SituationScene *const situation)
{
    if(!situation)
    {
        qCritical() << "Simulation Controller: situation scene cannot be nullptr";
        return;
    }

    situation_ = situation;
    start();
}

void SimulationController::stopSimulation()
{
    situation_ = nullptr;
    quit();
    wait();
}

void SimulationController::run()
{
    // create interface object and host it to the other processes
    SimulationInterface interface(situation_);
    const QString       url = "local:simulationInterfaceNode";

    QRemoteObjectHost interfaceNode(url);
    interfaceNode.enableRemoting(&interface);

    // run simulation
    QString             simulation_path = ".\\simulation\\SimulationEngine.exe";
    QStringList         arguments;
    QProcess            simulation;

    arguments << url;
    simulation.start(simulation_path, arguments);

    exec();
}
