#include <QFileInfo>
#include "baserobot.h"

BaseRobot::BaseRobot(const int id) :
    CommonInterfaceUser(), id_(id)
{
    sentToGUI_                = false;
    dispObj_.pixmapFilename   = "";
    dispObj_.pixmapDimensions = {32, 32};
    dispObj_.pixmapPosition   = {0, 0, 0.0};
}

BaseRobot::BaseRobot(const int id, const PositionType pos, const QString pixmap,
                     const RectDimentionsType dim, const BSIReplicaSP rep) :
    CommonInterfaceUser(rep), id_(id)
{
    sentToGUI_                = false;
    dispObj_.pixmapFilename   = pixmap;
    dispObj_.pixmapDimensions = dim;
    dispObj_.pixmapPosition   = pos;
}

BaseRobot::BaseRobot(const BaseRobot& robot) :
    CommonInterfaceUser(robot), id_(robot.id_)
{
    sentToGUI_ = robot.sentToGUI_;
    dispObj_   = robot.dispObj_;
}

BaseRobot::~BaseRobot()
{

}

bool BaseRobot::setInitialPixmapPosition(const PositionType pos)
{
    // the position may be set from outside only before sending it to GUI
    if(sentToGUI_)
    {
        return false;
    }

    updatePixmapPosition(pos);
    return true;
}

void BaseRobot::setPixmapFile(const QString pixmap)
{
    dispObj_.pixmapFilename = pixmap;

    // if robot has been sent to GUI, update the pixmap
    if(sentToGUI_ && isConnectedToTheInterface() && isPixmapFileValid(pixmap))
    {
        deletePixmap();
        addPixmap();
    }
}

void BaseRobot::setPixmapSize(const RectDimentionsType dim)
{
    dispObj_.pixmapDimensions = dim;

    // if robot has been sent to GUI, update its size
    if(sentToGUI_ && isConnectedToTheInterface())
    {
        deletePixmap();
        addPixmap();
    }
}

void BaseRobot::run()
{
    if(!addPixmap())
    {
        qCritical() << "Base Robot: cannot add robot (ID =" << id_ << ") to GUI";
        emit jobFinished();
        return;
    }
    runRobot();
    emit jobFinished();
}

bool BaseRobot::addPixmap()
{

    if(sentToGUI_                   ||
       !isConnectedToTheInterface() ||
       !isPixmapFileValid(dispObj_.pixmapFilename))
    {
        return false;
    }

    sentToGUI_ = true;
    emit addObjectReq(id_, dispObj_);
    return true;
}

bool BaseRobot::deletePixmap()
{
    if(!sentToGUI_ || !isConnectedToTheInterface())
    {
        return false;
    }

    sentToGUI_ = false;
    emit deleteObjectReq(id_);
    return true;
}

void BaseRobot::updatePixmapPosition(const PositionType pos)
{
    dispObj_.pixmapPosition = pos;

    if(sentToGUI_ && isConnectedToTheInterface())
    {
        emit updateObjectPositionReq(id_, dispObj_.pixmapPosition);
    }
}

bool BaseRobot::isPixmapFileValid(const QString file) const
{
    QFileInfo qfile(file);

    if(!qfile.exists() || !qfile.isFile())
    {
        return false;
    }
    return true;
}
