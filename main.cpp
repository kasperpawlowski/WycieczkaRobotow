#include "mainwindow.h"
#include <QApplication>

#include "simulation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    Simulation simulation("SIMULATION", window.getSituationPtr());
    simulation.start();

    return app.exec();
}
