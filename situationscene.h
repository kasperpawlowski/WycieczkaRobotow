#ifndef SITUATIONSCENE_H
#define SITUATIONSCENE_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "basictypes.h"

/*!
 * \brief The SituationScene class is a widget that allows to display various
 *        pixmaps at defined position on the screen.
 *
 * The class derives from QGraphicsScene which serves as a container for QGraphicsItems.
 * It is used together with QGraphicsView for visualizing graphical items.
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
    explicit SituationScene(QGraphicsView *const view, QObject *parent = nullptr);

    /*!
     * \brief ~SituationScene destructs the SituationScene
     */
    ~SituationScene() override {}

signals:
    /*!
     * \brief cannotAddObject emitted when a new object cannot be added
     * \param[in] id an identifier of an object
     *
     * Emmited when provided object is not valid.
     */
    void cannotAddObject(const int id);

    /*!
     * \brief cannotDeleteObject emmitted when the object cannot be deleted
     * \param[in] id an identifier of an object
     *
     * Emitted when the object of provided identifier does not exist (has not been
     * added yet).
     */
    void cannotDeleteObject(const int id);

    /*!
     * \brief cannotUpdateObjectPosition emmited when the object cannot be updated
     * \param[in] id an identifier of an object
     *
     * Emitted when the object of provided identifier does not exist (has not been
     * added yet).
     */
    void cannotUpdateObjectPosition(const int id);

    /*!
     * \brief situationRectDimensionsInfo emitted when requested for dimensions of
     *        the visualization area
     * \param[in] dim dimensions of the visualization area
     */
    void situationRectDimensionsInfo(const RectDimentionsType dim);

public slots:
    /*!
     * \brief clear clears the scene
     */
    void clear();

    /*!
     * \brief addObject adds a displayable object to the scene
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
     * \brief situationRectDimensions emits signal that holds dimensions
     *        of visualization area
     */
    void situationRectDimensions();

private:
    SituationScene() = delete;
    void setPixmapPosition(QGraphicsPixmapItem* pixmap, const PositionType& pos);
    bool objectExists(const int id) const;

    /*!
     * \brief isAddedObjectValid checks whether the object being added is valid
     * \param[in] id an identifier requested for an object being added
     * \param[in] obj an object being added
     * \return true when the object of provided id does not exist (has not been
     *         added yet), AND the pixmap file exists and has supported format, AND
     *         the pixmap dimensions are different than zero, otherwise false
     */
    bool isAddedObjectValid(const int id, const DisplayableObjectType& obj) const;

    typedef std::map<int, QGraphicsPixmapItem*>  SOContainer;
    typedef std::pair<int, QGraphicsPixmapItem*> SOMapPair;
    QGraphicsView* view_;
    SOContainer    objects_;
};

#endif // SITUATIONSCENE_H
