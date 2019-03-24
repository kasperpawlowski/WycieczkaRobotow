#include <QApplication>
#include <QThread>
#include "mainwindow.h"
#include "simulationcontroller.h"

const QString simulationPath = ".\\Simulation.exe";
const QString interfaceUrl   = "local:simulationInterfaceNode";

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath(".\\");
    QApplication         app(argc, argv);
    MainWindow           window;
    SimulationController simulation;
    QThread              thread;

    // set desired URL of Qt Remote Object interface and a custom simulation path
    simulation.setInterfaceURL(interfaceUrl);
    simulation.setSimulationFilePath(simulationPath);

    // connect signals and slots between the main window and the simulation controller
    QObject::connect(&window, SIGNAL(SimulationStartRequest(const SituationScene*)),
                     &simulation, SLOT(startSimulation(const SituationScene*)));

    QObject::connect(&window, SIGNAL(SimulationStopRequest()),
                     &simulation, SLOT(stopSimulation()));

    QObject::connect(&app, SIGNAL(aboutToQuit()),
                     &simulation, SLOT(stopSimulation()));

    window.showMaximized();
    simulation.moveToThread(&thread);
    thread.start();
    app.exec();

    // when returned from the main event loop, quit the auxiliary process also
    thread.quit();
    thread.wait();
    return 0;
}
