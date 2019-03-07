#include <QApplication>
#include <QThread>
#include "mainwindow.h"
#include "simulationcontroller.h"

int main(int argc, char *argv[])
{
    QApplication         app(argc, argv);
    MainWindow           window;
    SimulationController simulation;
    QThread              thread;
    //const QString path = ".\\simulation\\SimulationEngine.exe";
    const QString        path = "C:\\Users\\Kasper\\Desktop\\OKNO\\ZCpp\\build-SimulationEngine-Desktop_Qt_5_12_1_MinGW_64_bit-Release\\release\\SimulationEngine.exe";
    const QString        url  = "local:simulationInterfaceNode";

    // set desired URL of Qt Remote Object interface and a custom simulation path
    simulation.setInterfaceURL(url);
    simulation.setSimulationFilePath(path);

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
