#include "basictypes.h"
#include "simulation.h"

Simulation::Simulation(QString n, SituationScene *s) :
                       name_(n)
{
    qRegisterMetaType<DisplayableObjectType>("DisplayableObjectType");
    qRegisterMetaType<PositionType>("PositionType");

    connect(this, SIGNAL(addObject(const int, const DisplayableObjectType)),
            s, SLOT(addObject(const int, const DisplayableObjectType)));

    connect(this, SIGNAL(deleteObject(const int)),
            s, SLOT(deleteObject(const int)));

    connect(this, SIGNAL(updateObjectPosition(const int, const PositionType)),
            s, SLOT(updateObjectPosition(const int, const PositionType)));
}

void Simulation::run()
{
    QThread::msleep(1000);
    DisplayableObjectType obj[8];

    obj[0].pixmapPosition = {580, 400, 0.0};
    obj[1].pixmapPosition = {500, 400, 15.0};
    obj[2].pixmapPosition = {450, 400, 30.0};
    obj[3].pixmapPosition = {400, 400, 45.0};
    obj[4].pixmapPosition = {0, 0, 0.0};
    obj[5].pixmapPosition = {0, 817, -90.0};
    obj[6].pixmapPosition = {1171, 817, -90.0};
    obj[7].pixmapPosition = {1171, 0, 180.0};

    for(int i=0; i < 8; i++)
    {
        if((i == 0) || (i > 3))
        {
            obj[i].pixmapFilename   = "C:\\Users\\Kasper\\Desktop\\OKNO\\ZCpp\\WycieczkaRobotow\\pixmaps\\leader.png";
            obj[i].pixmapDimensions = {64, 64};
        }
        else
        {
            obj[i].pixmapFilename   = "C:\\Users\\Kasper\\Desktop\\OKNO\\ZCpp\\WycieczkaRobotow\\pixmaps\\troop.png";
            obj[i].pixmapDimensions = {32, 32};
        }
        emit addObject(i, obj[i]);
    }

    while(true)
    {
        const int step  = 2;
        const int sleep = 10;

        QThread::msleep(sleep);

        for (int i = 0; i < 4; ++i)
        {
            if((obj[i].pixmapPosition.x < 600) && (obj[i].pixmapPosition.y == 400))
            {
                obj[i].pixmapPosition.a -= 15.0;
                obj[i].pixmapPosition.x += step;
            }
            else
            {
                if((obj[i].pixmapPosition.y < 600) && (obj[i].pixmapPosition.x == 600))
                {
                    obj[i].pixmapPosition.y += step;
                }
                else
                {
                    if((obj[i].pixmapPosition.x > 400) && (obj[i].pixmapPosition.y == 600))
                    {
                        obj[i].pixmapPosition.a += 15.0;
                        obj[i].pixmapPosition.x -= step;
                    }
                    else
                    {
                        if((obj[i].pixmapPosition.y > 400) && (obj[i].pixmapPosition.x == 400))
                        {
                            obj[i].pixmapPosition.y -= step;
                        }
                    }
                }
            }
            emit updateObjectPosition(i, obj[i].pixmapPosition);
        }
    }
}
