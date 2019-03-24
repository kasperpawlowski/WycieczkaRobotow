#include <QCoreApplication>
#include "simulationstarter.h"
#include "followtheleadersimulation.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        qCritical() << "Simulation Engine: simulation interface URL must be provided as an input argument";
        return 1;
    }

    QCoreApplication a(argc, argv);
    SimulationStarter<FollowTheLeaderSimulation> simStarter(&a, argv[1]);

    return a.exec();
}
