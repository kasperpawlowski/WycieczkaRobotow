#include <QApplication>
#include "mainwindow.h"
#include "simulationcontroller.h"

int main(int argc, char *argv[])
{
    QApplication         app(argc, argv);
    MainWindow           window;
    SimulationController simController;

    // connect signals and slots between the main window and the simulation controller
    QObject::connect(&window, SIGNAL(SimulationStartRequest(const SituationScene *const)),
                     &simController, SLOT(startSimulation(const SituationScene *const)));

    QObject::connect(&window, SIGNAL(SimulationStopRequest()),
                     &simController, SLOT(stopSimulation()));

    window.showMaximized();
    return app.exec();
}
