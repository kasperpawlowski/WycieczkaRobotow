#include <QFileInfo>
#include "commoninterfaceuser.h"

CommonInterfaceUser::CommonInterfaceUser(const int id, const BSIReplicaSP rep) :
    QObject(nullptr), id_(id)
{
    connected_   = false;
    sentToGUI_   = false;
    scaleFactor_ = 1.0;
    dispObj_.pixmapPosition   = {0, 0, 0.0};
    dispObj_.pixmapFilename   = "";
    dispObj_.pixmapDimensions = {32, 32};
    connectToTheInterface(rep);
}

CommonInterfaceUser::CommonInterfaceUser(const CommonInterfaceUser& user) :
    QObject(nullptr), id_(user.id_)
{
    sentToGUI_   = user.sentToGUI_;
    scaleFactor_ = user.scaleFactor_;
    dispObj_     = user.dispObj_;

    // as QObject does not have a copy constructor, new object has to be
    // created, therefore all the connections have to be made again
    connected_ = false;
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

void CommonInterfaceUser::setPixmapFile(const QString pixmap)
{
    dispObj_.pixmapFilename = pixmap;

    // if robot has been sent to GUI, update the pixmap
    if(isSentToGUI()               &&
       isConnectedToTheInterface() &&
       isPixmapFileValid(pixmap))
    {
        deletePixmap();
        addPixmap();
    }
}

void CommonInterfaceUser::setPixmapSize(const RectDimensionsType dim)
{
    dispObj_.pixmapDimensions = dim;

    // if robot has been sent to GUI, update its size
    if(isSentToGUI() && isConnectedToTheInterface())
    {
        deletePixmap();
        addPixmap();
    }
}

bool CommonInterfaceUser::isConnectedToTheInterface() const
{
    return connected_;
}

bool CommonInterfaceUser::addPixmap()
{
    if(isSentToGUI()                ||
       !isConnectedToTheInterface() ||
       !isPixmapFileValid(dispObj_.pixmapFilename))
    {
        return false;
    }

    sentToGUI_ = true;
    emit addObjectReq(id_, dispObj_);
    return true;
}

bool CommonInterfaceUser::deletePixmap()
{
    if(!isSentToGUI() || !isConnectedToTheInterface())
    {
        return false;
    }

    sentToGUI_ = false;
    emit deleteObjectReq(id_);
    return true;
}

void CommonInterfaceUser::updatePixmapPosition(const PositionType pos)
{
    dispObj_.pixmapPosition = pos;

    if(sentToGUI_ && isConnectedToTheInterface())
    {
        emit updateObjectPositionReq(id_, dispObj_.pixmapPosition);
    }
}

bool CommonInterfaceUser::isPixmapFileValid(const QString file) const
{
    QFileInfo qfile(file);

    if(!qfile.exists() || !qfile.isFile())
    {
        return false;
    }
    return true;
}
