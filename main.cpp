#include "mainwindow.h"
#include <QApplication>

#include "simulation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.showMaximized();

    //Simulation simulation("SIMULATION", window.getSituationData());
    //simulation.start();

    return app.exec();
}
