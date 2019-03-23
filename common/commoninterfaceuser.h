#ifndef COMMONINTERFACEUSER_H
#define COMMONINTERFACEUSER_H

#include <QObject>
#include "rep_basesimulationinterface_replica.h"

/*!
 * \brief BSIReplicaSP an alias for BaseSimulationInterfaceReplica shared pointer
 */
typedef QSharedPointer<BaseSimulationInterfaceReplica> BSIReplicaSP;

/*!
 * \brief The CommonInterfaceUser class provides connection to the GUI along
 *        with basic commands
 *
 * This class lets to add objects to, delete objects from and update their position
 * on the SituationScene of the GUI.
 */
class CommonInterfaceUser : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief CommonInterfaceUser constructs a new CommonInterfaceUser connected to
     *        the provided Qt Remote Object simulation interface replica
     * \param[in] id an identifier of an interface user
     */
    CommonInterfaceUser(const int id, const BSIReplicaSP rep);

    /*!
     * \brief CommonInterfaceUser a copy constructor
     */
    CommonInterfaceUser(const CommonInterfaceUser& user);

    /*!
     * \brief ~CommonInterfaceUser destructs the CommonInterfaceUser
     */
    virtual ~CommonInterfaceUser();

    /*!
     * \brief connectToTheInterface connects to the interface
     * \param[in] rep a pointer to the Qt Remote Object inteface replica
     * \return true on success, false otherwise
     */
    bool connectToTheInterface(BSIReplicaSP rep);

    /*!
     * \brief setScaleFactor sets the scale factor that is used for translation
     *        from world coordinates to SituationScene coordinates
     * \param[in] f scale factor
     */
    void setScaleFactor(double f) {scaleFactor_ = f;}

    /*!
     * \brief setPixmapFile sets a path to the displayed pixmap file
     * \param[in] pixmap a path to the pixmap file
     */
    void setPixmapFile(const QString pixmap);

    /*!
     * \brief setPixmapSize sets size of the displayed pixmap
     * \param[in] dim size of the pixmap
     */
    void setPixmapSize(const RectDimensionsType dim);

    /*!
     * \brief getID returns the identifier of the robot
     */
    int getID() const {return id_;}

    /*!
     * \brief isConnectedToTheInterface checks whether the object is properly
     *        connected to the interface
     * \return true when properly connected, false otherwise
     */
    bool isConnectedToTheInterface() const;

    /*!
     * \brief isSentToGUI
     * \return true when the object has already been added to the SituationScene,
     *         false otherwise
     */
    bool isSentToGUI() const {return sentToGUI_;}

    /*!
     * \brief getScaleFactor returns previously set scale factor
     * \return
     */
    double getScaleFactor() const {return scaleFactor_;}

    /*!
     * \brief getPixmapPosition returns current position of the displayed pixmap
     */
    PositionType getPixmapPosition() const {return dispObj_.pixmapPosition;}

    /*!
     * \brief getPixmapFile returns a path to the file of the displayed pixmap
     */
    QString getPixmapFile() const {return dispObj_.pixmapFilename;}

    /*!
     * \brief getPixmapSize returns current size of the displayed pixmap
     * \return
     */
    RectDimensionsType getPixmapSize() const {return dispObj_.pixmapDimensions;}

signals:
    /*!
     * \brief addObjectReq may be emitted by the user to add a displayable object
     *        to the SituationScene
     * \param[in] id an identifier of the added object
     * \param[in] obj the added object
     */
    void addObjectReq(const int id, const DisplayableObjectType obj);

    /*!
     * \brief deleteObjectReq may be emitted by the user to delete the object
     *        from the SituationScene
     * \param[in] id an identifier of the deleted object
     */
    void deleteObjectReq(const int id);

    /*!
     * \brief updateObjectPositionReq may be emitted by the user to update the
     *        position of the object described by the provided identifier on
     *        the SituationScene
     * \param[in] id an identifier of the updated object
     * \param[in] pos a new position of the updated object
     */
    void updateObjectPositionReq(const int id, const PositionType pos);

public:
    /*!
     * \brief addPixmap adds the pixmap to the SituationScene
     * \return true on success, false otherwise
     */
    virtual bool addPixmap();

    /*!
     * \brief deletePixmap deletes the pixmap from the SituationScene
     * \return true on success, false otherwise
     */
    virtual bool deletePixmap();

    /*!
     * \brief updatePixmapPosition updates the position of the pixmap on the SituationScene
     * \param[in] pos new position
     */
    virtual void updatePixmapPosition(const PositionType pos);

private:
    CommonInterfaceUser() = delete ;
    bool isPixmapFileValid(const QString file) const;

    const int             id_;
    bool                  connected_;
    bool                  sentToGUI_;
    double                scaleFactor_;
    BSIReplicaSP          replicaInterface_;
    DisplayableObjectType dispObj_;
};

#endif // COMMONINTERFACEUSER_H
