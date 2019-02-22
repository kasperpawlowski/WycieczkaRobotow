#include "basictypes.h"
#include "simulation.h"

Simulation::Simulation(QString n, SituationData *s) :
                       name_(n), situation_(s)
{

}

void Simulation::run()
{
    DisplayableObjectType obj[4];

    obj[0].pixmapPosition = {300, 200, 0.0};
    obj[1].pixmapPosition = {200, 300, 30.0};
    obj[2].pixmapPosition = {100, 200, 60.0};
    obj[3].pixmapPosition = {200, 100, 90.0};

    for(int i=0; i < 4; i++)
    {
        if(i == 0)
        {
            obj[i].pixmapFilename   = "C:\\Users\\Kasper\\Desktop\\OKNO\\ZCpp\\WycieczkaRobotow\\pixmaps\\leader.png";
            obj[i].pixmapDimensions = {48, 48};
        }
        else
        {
            obj[i].pixmapFilename   = "C:\\Users\\Kasper\\Desktop\\OKNO\\ZCpp\\WycieczkaRobotow\\pixmaps\\troop.png";
            obj[i].pixmapDimensions = {32, 32};
        }
        situation_->addObject(i, obj[i]);
    }

    while(true)
    {
        //QThread::msleep(1000);
        for(int i=0; i<10000000; i++);

        PositionType tmp = obj[0].pixmapPosition;
        obj[0].pixmapPosition = obj[3].pixmapPosition;
        obj[1].pixmapPosition = obj[2].pixmapPosition;
        obj[2].pixmapPosition = obj[3].pixmapPosition;
        obj[3].pixmapPosition = tmp;

        for(int i=0; i < 4; i++)
        {
            situation_->updateObjectPosition(i, obj[i].pixmapPosition);
        }
    }
}
