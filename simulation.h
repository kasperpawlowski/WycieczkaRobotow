#ifndef SIMULATION_H
#define SIMULATION_H

#include <QThread>
#include "situationdata.h"

class Simulation : public QThread
{
public:
    Simulation(QString n, SituationData *s);
    void run();
private:
    Simulation();
    QString        name_;
    SituationData* situation_;
};

#endif // SIMULATION_H
