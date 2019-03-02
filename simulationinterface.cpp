#include "simulationinterface.h"

SimulationInterface::SimulationInterface(const SituationScene *const situation, QObject *parent) :
    BaseSimulationInterfaceSource(parent)
{
    connections_.push_back(connect(this, SIGNAL(clearReqFwd()),
                                   situation, SLOT(clear())));

    connections_.push_back(connect(this, SIGNAL(addObjectReqFwd(const int, const DisplayableObjectType)),
                                   situation, SLOT(addObject(const int, const DisplayableObjectType))));

    connections_.push_back(connect(this, SIGNAL(deleteObjectReqFwd(const int)),
                                   situation, SLOT(deleteObject(const int))));

    connections_.push_back(connect(this, SIGNAL(updateObjectPositionReqFwd(const int, const PositionType)),
                                   situation, SLOT(updateObjectPosition(const int, const PositionType))));

    connections_.push_back(connect(this, SIGNAL(situationRectDimensionsReqFwd()),
                                   situation, SLOT(situationRectDimensions())));

    connections_.push_back(connect(situation, SIGNAL(situationRectDimensionsInfo(const RectDimentionsType)),
                                   this, SLOT(situationRectDimensionsInfoReemit(const RectDimentionsType))));

    connections_.push_back(connect(situation, SIGNAL(cannotAddObject(const int)),
                                   this, SLOT(cannotAddObjectReemit(const int))));

    connections_.push_back(connect(situation, SIGNAL(cannotDeleteObject(const int)),
                                   this, SLOT(cannotDeleteObjectReemit(const int))));

    connections_.push_back(connect(situation, SIGNAL(cannotUpdateObjectPosition(const int)),
                                   this, SLOT(cannotUpdateObjectPositionReemit(const int))));
}

SimulationInterface::~SimulationInterface()
{
    for(ConnectionsContainer::iterator it = connections_.begin(); it != connections_.end(); ++it)
    {
        disconnect(*it);
    }
    connections_.clear();
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
