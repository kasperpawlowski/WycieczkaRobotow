#include <QDebug>
#include <QFileInfo>
#include <set>
#include "situationscene.h"

SituationScene::SituationScene(QGraphicsView* view, QObject *parent) :
    QGraphicsScene(parent), view_(view)
{
    setSceneRect(view_->rect());
    view_->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view_->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view_->setScene(this);
    objects_.clear();
}

SituationScene::~SituationScene()
{
}

void SituationScene::addObject(const int id, const DisplayableObjectType obj)
{
    if(!isAddedObjectValid(id, obj))
    {
        emit cannotAddObject(id);
    }

    QPixmap scaled_pixmap(QString::fromStdString(obj.pixmapFilename));
    scaled_pixmap = scaled_pixmap.scaledToWidth(obj.pixmapDimensions.width);
    scaled_pixmap = scaled_pixmap.scaledToHeight(obj.pixmapDimensions.height);

    objects_.insert(SOMapPair(id, addPixmap(scaled_pixmap)));

    QGraphicsPixmapItem* inserted = objects_.at(id);

    inserted->setTransformOriginPoint(inserted->boundingRect().center());
    setPixmapPosition(objects_.at(id), obj.pixmapPosition);
}

void SituationScene::deleteObject(const int id)
{
    if(!objectExists(id))
    {
        emit cannotDeleteObject(id);
    }

    removeItem(objects_.at(id));
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

void SituationScene::situationRectDimensionsRequest(const int id)
{
    RectDimentionsType dim;
    dim.height = int(sceneRect().height());
    dim.width  = int(sceneRect().width());
    emit situationRectDimensions(id, dim);
}

void SituationScene::setPixmapPosition(QGraphicsPixmapItem* pixmap, const PositionType& pos)
{
    QRectF rect(sceneRect());

    pixmap->setX(pos.x - pixmap->boundingRect().width()/2);
    pixmap->setY(-(pos.y - rect.height()) - pixmap->boundingRect().width()/2);
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
    QFileInfo file(QString::fromStdString(obj.pixmapFilename));
    std::set<QString> supported_files = {"bmp", "gif", "jpg", "jpeg", "png", "pbm", "pgm", "ppm", "xbm", "xpm"};

    if(objectExists(id))
    {
        result = false;
        qWarning() << "The object with very same ID already exists. ID = " << id;
    }

    if(!file.exists() ||
       !file.isFile() ||
       (supported_files.find(file.suffix()) == supported_files.end()))
    {
        result = false;
        qWarning() << "There is a problem with the pixmap file of the object being added";
    }

    if((obj.pixmapDimensions.width  == 0) ||
       (obj.pixmapDimensions.height == 0))
    {
        result = false;
        qWarning() << "The object being added must have dimensions greater than zero";
    }
    return result;
}
