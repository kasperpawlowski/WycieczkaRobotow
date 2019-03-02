#include <QDebug>
#include <QFileInfo>
#include <set>
#include "situationscene.h"

SituationScene::SituationScene(QGraphicsView *const view, QObject *parent) :
    QGraphicsScene(parent), view_(view)
{
    if(!view)
    {
        qCritical() << "Situation Scene: view cannot be nullptr";
        return;
    }

    qRegisterMetaType<SituationScene*>("SituationScene*");
    view_->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view_->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view_->setScene(this);
    clear();
}

void SituationScene::clear()
{
    for(SOContainer::iterator it = objects_.begin(); it != objects_.end(); ++it)
    {
        removeItem(it->second);
    }
    objects_.clear();
    update();
}

void SituationScene::addObject(const int id, const DisplayableObjectType obj)
{
    if(!isAddedObjectValid(id, obj))
    {
        emit cannotAddObject(id);
        return;
    }

    QPixmap scaled_pixmap = QPixmap(obj.pixmapFilename).scaled(obj.pixmapDimensions.width, obj.pixmapDimensions.height);

    objects_.insert(SOMapPair(id, addPixmap(scaled_pixmap)));
    objects_.at(id)->setTransformOriginPoint(objects_.at(id)->boundingRect().center());
    setPixmapPosition(objects_.at(id), obj.pixmapPosition);
}

void SituationScene::deleteObject(const int id)
{
    if(!objectExists(id))
    {
        emit cannotDeleteObject(id);
        return;
    }

    removeItem(objects_.at(id));
    objects_.erase(id);
    update();
}

void SituationScene::updateObjectPosition(const int id, const PositionType pos)
{
    if(!objectExists(id))
    {
        emit cannotUpdateObjectPosition(id);
    }
    else
    {
        setPixmapPosition(objects_.at(id), pos);
    }
}

void SituationScene::situationRectDimensions()
{
    // first, set the scene rectangle based on view widget
    setSceneRect(view_->rect());

    RectDimentionsType dim;
    dim.height = view_->rect().height();
    dim.width  = view_->rect().width();
    emit situationRectDimensionsInfo(dim);
}

void SituationScene::setPixmapPosition(QGraphicsPixmapItem* pixmap, const PositionType& pos)
{
    QRectF rect = sceneRect();
    pixmap->setX(pos.x + rect.x() - pixmap->boundingRect().width()/2);
    pixmap->setY(-(pos.y - rect.height()) + rect.y() - pixmap->boundingRect().height()/2);
    pixmap->setRotation(90.0 - pos.a);
    update();
}

bool SituationScene::objectExists(const int id) const
{
    if(objects_.find(id) == objects_.end())
    {
        return false;
    }
    return true;
}

bool SituationScene::isAddedObjectValid(const int id, const DisplayableObjectType& obj) const
{
    bool result = true;
    QFileInfo file(obj.pixmapFilename);
    std::set<QString> supported_files = {"bmp", "gif", "jpg", "jpeg", "png", "pbm", "pgm", "ppm", "xbm", "xpm"};

    if(objectExists(id))
    {
        result = false;
        qWarning() << "Situation Scene: the object with very same ID already exists. ID = " << id;
    }

    if(!file.exists() ||
       !file.isFile() ||
       (supported_files.find(file.suffix()) == supported_files.end()))
    {
        result = false;
        qWarning() << "Situation Scene: incorrect pixmap file of the object being added";
    }

    if((obj.pixmapDimensions.width  == 0) ||
       (obj.pixmapDimensions.height == 0))
    {
        result = false;
        qWarning() << "Situation Scene: the object being added must have dimensions greater than zero";
    }
    return result;
}
