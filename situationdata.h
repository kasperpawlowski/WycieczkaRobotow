#ifndef SITUATIONDATA_H
#define SITUATIONDATA_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "basictypes.h"

class SituationData : public QObject
{
    Q_OBJECT

public:
    SituationData(QGraphicsView* v);
    ~SituationData();

public slots:
    void addObject(const int id, const DisplayableObjectType obj);
    void deleteObject(const int id);
    void updateObjectPosition(const int id, const PositionType pos);
    void situationRectDimensionsRequest(const int id);

signals:
    void cannotAddObject(const int id);
    void cannotDeleteObject(const int id);
    void cannotUpdateObjectPosition(const int id);
    void situationRectDimensions(const int id, const RectDimentionsType dim);

private:
    typedef std::map<int, QGraphicsPixmapItem*> SOContainer;
    SituationData();
    void setPixmapPosition(QGraphicsPixmapItem* pixmap, const PositionType& pos);
    bool objectExists(const int id);
    bool isAddedObjectValid(const int id, const DisplayableObjectType& obj);
    QGraphicsView*  view_;
    QGraphicsScene* scene_;
    SOContainer     objects_;
};

#endif // SITUATIONDATA_H
