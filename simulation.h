#ifndef SIMULATION_H
#define SIMULATION_H

#include <QThread>
#include "basictypes.h"
#include "situationscene.h"

class Simulation : public QThread
{
    Q_OBJECT
public:
    Simulation(QString n, SituationScene *s);
    void run();

signals:
    void addObject(const int id, const DisplayableObjectType obj);
    void deleteObject(const int id);
    void updateObjectPosition(const int id, const PositionType pos);

private:
    Simulation();
    QString name_;
};

#endif // SIMULATION_H
