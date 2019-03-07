#ifndef BASEROBOT_H
#define BASEROBOT_H

#include <QObject>
#include "commoninterfaceuser.h"

/*!
 * \brief The BaseRobot class is an abstract robot class that has an access to
 *        the GUI in order to display a pixmap that represents it on the screen
 *
 * BaseRobot derives from CommonInterfaceUser to have an access to the interface
 * connecting to the SituationScene. Provides basic methods to display itself,
 * delete itself from the screen or update its position.
 */
class BaseRobot : public CommonInterfaceUser
{
    Q_OBJECT
public:
    /*!
     * \brief BaseRobot creates a new BaseRobot described by the provided identifier
     * \param[in] id an identifier that will describe the robot
     */
    BaseRobot(const int id);

    /*!
     * \brief BaseRobot creates a new BaseRobot described by the provided identifier
     * \param[in] id an identifier that will describe the robot
     * \param[in] pos initial position of the robot on the screen
     * \param[in] pixmap a file path to the pixmap that will be displayed
     * \param[in] dim dimensions of the pixmap that will be displayed
     * \param[in] rep a pointer to the Qt Remote Object simulation inteface replica
     */
    BaseRobot(const int id, const PositionType pos, const QString pixmap,
              const RectDimentionsType dim, const BSIReplicaSP rep);

    /*!
     * \brief BaseRobot a copy constructor
     */
    BaseRobot(const BaseRobot& robot);

    /*!
     * \brief ~BaseRobot destructs the BaseRobot
     */
    virtual ~BaseRobot();

    /*!
     * \brief clone polymorphic copy constructor, must be defined in every
     *        class that derives from BaseRobot
     * \return pointer to a newly created copy of the object
     */
    virtual BaseRobot* clone() const = 0;

    /*!
     * \brief setInitialPixmapPosition sets initial pixmap position on SituationScene
     * \param[in] pos initial position
     * \return true on success, false otherwise
     */
    bool setInitialPixmapPosition(const PositionType pos);

    /*!
     * \brief setPixmapFile sets a path to the displayed pixmap file
     * \param[in] pixmap a path to the pixmap file
     */
    void setPixmapFile(const QString pixmap);

    /*!
     * \brief setPixmapSize sets size of the displayed pixmap
     * \param[in] dim size of the pixmap
     */
    void setPixmapSize(const RectDimentionsType dim);

    /*!
     * \brief getID returns the identifier of the robot
     */
    int getID() const {return id_;}

    /*!
     * \brief getPixmapPosition returns current position of the displayed pixmap
     */
    PositionType getPixmapPosition() const {return dispObj_.pixmapPosition;}

    /*!
     * \brief getPixmapFile returns a path to the file of the displayed pixmap
     */
    QString getPixmapFile() const {return  dispObj_.pixmapFilename;}

    /*!
     * \brief getPixmapSize returns current size of the displayed pixmap
     * \return
     */
    RectDimentionsType getPixmapSize() const {return  dispObj_.pixmapDimensions;}

signals:
    /*!
     * \brief jobFinished emitted when the robot finishes its role
     */
    void jobFinished();

public slots:
    /*!
     * \brief run callable entry point of the robot simulation
     */
    void run();

protected:
    /*!
     * \brief addPixmap adds the pixmap to the SituationScene
     * \return true on success, false otherwise
     */
    bool addPixmap();

    /*!
     * \brief deletePixmap deletes the pixmap from the SituationScene
     * \return true on success, false otherwise
     */
    bool deletePixmap();

    /*!
     * \brief updatePixmapPosition updates the position of the pixmap on the SituationScene
     * \param[in] pos new position
     */
    void updatePixmapPosition(const PositionType pos);

private:
    BaseRobot() = delete;
    bool isPixmapFileValid(const QString file) const;

    /*!
     * \brief runRobot shall be defined by classes that derive from BaseRobot
     *
     * This is the real entry point of the simulation for each robot. The robot
     * simulation logic shall be defined in this method. QCoreApplication::processEvents()
     * should be called periodically in a loop so the robot keeps being responsive. It is assumed
     * than when the robot returns from this method its job is finished.
     */
    virtual void runRobot() = 0;

    const int             id_;
    DisplayableObjectType dispObj_;
    bool                  sentToGUI_;
};

#endif // BASEROBOT_H
