#include "simulationinterface.h"

SimulationInterface::SimulationInterface(const SituationScene *const situation, QObject *parent) :
    BaseSimulationInterfaceSource(parent)
{
    connect(this, SIGNAL(clearReqFwd()),
            situation, SLOT(clear()));

    connect(this, SIGNAL(addObjectReqFwd(const int, const DisplayableObjectType)),
            situation, SLOT(addObject(const int, const DisplayableObjectType)));

    connect(this, SIGNAL(deleteObjectReqFwd(const int)),
            situation, SLOT(deleteObject(const int)));

    connect(this, SIGNAL(updateObjectPositionReqFwd(const int, const PositionType)),
            situation, SLOT(updateObjectPosition(const int, const PositionType)));

    connect(this, SIGNAL(situationRectDimensionsReqFwd()),
            situation, SLOT(situationRectDimensions()));

    connect(situation, SIGNAL(situationRectDimensionsInfo(const RectDimentionsType)),
            this, SLOT(situationRectDimensionsInfoReemit(const RectDimentionsType)));

    connect(situation, SIGNAL(cannotAddObject(const int)),
            this, SLOT(cannotAddObjectReemit(const int)));

    connect(situation, SIGNAL(cannotDeleteObject(const int)),
            this, SLOT(cannotDeleteObjectReemit(const int)));

    connect(situation, SIGNAL(cannotUpdateObjectPosition(const int)),
            this, SLOT(cannotUpdateObjectPositionReemit(const int)));

    connect(this, SIGNAL(simulationFinishedFwd()),
            situation, SLOT(simulationFinished()));
}

void SimulationInterface::clearReqReemit()
{
    emit clearReqFwd();
}

void SimulationInterface::addObjectReqReemit(const int id, const DisplayableObjectType obj)
{
    emit addObjectReqFwd(id, obj);
}

void SimulationInterface::deleteObjectReqReemit(const int id)
{
    emit deleteObjectReqFwd(id);
}

void SimulationInterface::updateObjectPositionReqReemit(const int id, const PositionType pos)
{
    emit updateObjectPositionReqFwd(id, pos);
}

void SimulationInterface::situationRectDimensionsReqReemit()
{
    emit situationRectDimensionsReqFwd();
}

void SimulationInterface::situationRectDimensionsInfoReemit(const RectDimentionsType rect)
{
    emit situationRectDimensionsInfoFwd(rect);
}

void SimulationInterface::cannotAddObjectReemit(const int id)
{
    emit cannotAddObjectFwd(id);
}

void SimulationInterface::cannotDeleteObjectReemit(const int id)
{
    emit cannotDeleteObjectFwd(id);
}

void SimulationInterface::cannotUpdateObjectPositionReemit(const int id)
{
    emit cannotUpdateObjectPositionFwd(id);
}

void SimulationInterface::simulationFinishedReemit()
{
    emit simulationFinishedFwd();
}
