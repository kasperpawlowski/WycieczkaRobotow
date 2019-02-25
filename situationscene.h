#ifndef SITUATIONDATA_H
#define SITUATIONDATA_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "basictypes.h"

/*!
 * \brief The SituationScene class is a widget that allows to display various
 *        pixmaps at defined position on the screen.
 */
class SituationScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /*!
     * \brief SituationScene constructs a new SituationScene
     * \param[in] view a QGraphicsView object that the widget will be connected to
     * \param[in] parent a parent widget
     */
    explicit SituationScene(QGraphicsView* view, QObject *parent = nullptr);
    ~SituationScene();

signals:
    /*!
     * \brief cannotAddObject emitted when a new object cannot be added
     * \param[in] id an identifier of a object
     *
     * Emmited when provided object is not valid (\sa isAddedObjectValid()).
     */
    void cannotAddObject(const int id);

    /*!
     * \brief cannotDeleteObject emmitted when the object cannot be deleted
     * \param[in] id an identifier of a object
     *
     * Emitted when the object of provided identifier does not exist (has not been
     * added yet).
     */
    void cannotDeleteObject(const int id);

    /*!
     * \brief cannotUpdateObjectPosition emmited when the object cannot be updated
     * \param[in] id an identifier of a object
     *
     * Emitted when the object of provided identifier does not exist (has not been
     * added yet).
     */
    void cannotUpdateObjectPosition(const int id);

    /*!
     * \brief situationRectDimensions emitted when requested for dimensions of
     *        the visualization rectangle.
     * \param[in] id an identifier of the object that sent the request
     * \param[in] dim dimensions of the visualization area
     */
    void situationRectDimensions(const int id, const RectDimentionsType dim);

public slots:
    /*!
     * \brief addObject adds a displayable object so it can be displayed
     * \param[in] id an identifier of the added object
     * \param[in] obj the added object
     */
    void addObject(const int id, const DisplayableObjectType obj);

    /*!
     * \brief deleteObject deletes the object described by provided identifier
     * \param[in] id an identifier of the deleted object
     */
    void deleteObject(const int id);

    /*!
     * \brief updateObjectPosition updates position of the object described by
     *        provided identifier
     * \param[in] id an identifier of the updated object
     * \param[in] pos a new position of the updated object
     */
    void updateObjectPosition(const int id, const PositionType pos);

    /*!
     * \brief situationRectDimensionsRequest emits signal that holds dimensions
     *        of visualization rectangle (\sa situationRectDimensions())
     * \param[in] id an identifier of the object that requests dimensions of
     *            visualization area
     */
    void situationRectDimensionsRequest(const int id);

private:
    typedef std::map<int, QGraphicsPixmapItem*>  SOContainer;
    typedef std::pair<int, QGraphicsPixmapItem*> SOMapPair;

    SituationScene() = delete;
    void setPixmapPosition(QGraphicsPixmapItem* pixmap, const PositionType& pos);
    bool objectExists(const int id) const;

    /*!
     * \brief isAddedObjectValid checks whether the object being added is valid
     * \param[in] id an identifier requested for an object being added
     * \param[in] obj an object being added
     * \return true when the object of provided id does not exist (has not been
     *         added yet, AND the pixmap file exists and has supported format, AND
     *         the pixmap dimensions are different than zero, otherwise false
     */
    bool isAddedObjectValid(const int id, const DisplayableObjectType& obj) const;

    QGraphicsView*  view_;
    SOContainer     objects_;
};

#endif // SITUATIONDATA_H
