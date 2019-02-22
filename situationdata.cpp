#include <QDebug>
#include <QFileInfo>
#include <set>
#include "situationdata.h"

SituationData::SituationData(QGraphicsView* v) :
    view_(v), scene_(new QGraphicsScene)
{
    scene_->setSceneRect(view_->geometry());
    view_->setScene(scene_);
    objects_.clear();
}

SituationData::~SituationData()
{
    delete scene_;
}

void SituationData::addObject(const int id, const DisplayableObjectType obj)
{
    if(!isAddedObjectValid(id, obj))
    {
        emit cannotAddObject(id);
    }

    QPixmap scaled_pixmap(QString::fromStdString(obj.pixmapFilename));
    scaled_pixmap = scaled_pixmap.scaledToWidth(obj.pixmapDimensions.width);
    scaled_pixmap = scaled_pixmap.scaledToHeight(obj.pixmapDimensions.height);

    objects_.insert(std::pair<int, QGraphicsPixmapItem*>
                    (id, scene_->addPixmap(scaled_pixmap)));

    QGraphicsPixmapItem* inserted = objects_.at(id);

    inserted->setTransformOriginPoint(inserted->boundingRect().center());
    setPixmapPosition(objects_.at(id), obj.pixmapPosition);
}

void SituationData::deleteObject(const int id)
{
    if(!objectExists(id))
    {
        emit cannotDeleteObject(id);
    }

    scene_->removeItem(objects_.at(id));
    scene_->update();
}

void SituationData::updateObjectPosition(const int id, const PositionType pos)
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

void SituationData::situationRectDimensionsRequest(const int id)
{
    RectDimentionsType dim;
    dim.height = int(scene_->sceneRect().height());
    dim.width  = int(scene_->sceneRect().width());
    emit situationRectDimensions(id, dim);
}

void SituationData::setPixmapPosition(QGraphicsPixmapItem* pixmap, const PositionType& pos)
{
    QRectF rect(scene_->sceneRect());

    pixmap->setX(pos.x + rect.x() - pixmap->boundingRect().width()/2);
    pixmap->setY(-(pos.y - rect.height()) + rect.y() - pixmap->boundingRect().width()/2);
    pixmap->setRotation(90.0 - pos.a);
    scene_->update();
}

bool SituationData::objectExists(const int id)
{
    if(objects_.find(id) == objects_.end())
    {
        return false;
    }
    return true;
}

bool SituationData::isAddedObjectValid(const int id, const DisplayableObjectType& obj)
{
    bool result = true;
    QFileInfo file(QString::fromStdString(obj.pixmapFilename));
    std::set<QString> supported_files = {"bmp", "gif", "jpg", "jpeg", "png", "pbm", "pgm", "ppm", "xbm", "xpm"};

    if(objectExists(id))
    {
        result = false;
        qCritical() << "The object with very same ID already exists. ID = " << id;
    }

    if(!file.exists() ||
       !file.isFile() ||
       (supported_files.find(file.suffix()) == supported_files.end()))
    {
        result = false;
        qCritical() << "There is a problem with the pixmap file of the object being added";
    }

    if((obj.pixmapDimensions.width  == 0) ||
       (obj.pixmapDimensions.height == 0))
    {
        result = false;
        qCritical() << "The object being added must have dimensions greater than zero";
    }
    return result;
}
