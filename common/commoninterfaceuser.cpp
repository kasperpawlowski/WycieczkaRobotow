#include "commoninterfaceuser.h"

CommonInterfaceUser::CommonInterfaceUser() :
    QObject(nullptr), connected_(false)
{

}


CommonInterfaceUser::CommonInterfaceUser(const BSIReplicaSP rep) :
    QObject(nullptr), connected_(false)
{
    connectToTheInterface(rep);
}

CommonInterfaceUser::CommonInterfaceUser(const CommonInterfaceUser& user) :
    QObject(nullptr), connected_(false)
{
    // as QObject does not have copy constructor, new object has to be
    // created, therefore all the connections have to be made again
    connectToTheInterface(user.replicaInterface_);
}

CommonInterfaceUser::~CommonInterfaceUser()
{

}

bool CommonInterfaceUser::connectToTheInterface(BSIReplicaSP rep)
{
    // every interface user may connect only once
    if(rep.isNull() || connected_)
    {
        return false;
    }

    replicaInterface_ = rep;

    connect(this, SIGNAL(addObjectReq(const int, const DisplayableObjectType)),
            replicaInterface_.data(), SLOT(addObjectReqReemit(const int, const DisplayableObjectType)));

    connect(this, SIGNAL(deleteObjectReq(const int)),
            replicaInterface_.data(), SLOT(deleteObjectReqReemit(const int)));

    connect(this, SIGNAL(updateObjectPositionReq(const int, const PositionType)),
            replicaInterface_.data(), SLOT(updateObjectPositionReqReemit(const int, const PositionType)));

    connected_ = true;
    return true;
}

bool CommonInterfaceUser::isConnectedToTheInterface() const
{
    return (connected_ && replicaInterface_.data()->isReplicaValid());
}
