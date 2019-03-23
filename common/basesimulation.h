#ifndef BASESIMULATION_H
#define BASESIMULATION_H

#include <QTimer>
#include "basictypes.h"
#include "robotsmanager.h"

/*!
 * \brief The BaseSimulation class is an abstract simulation class that has an
 *        access to the GUI and manages simulation. Contains RobotsManager that
 *        takes care of robots' separate threads
 */
class BaseSimulation : public QObject
{
    Q_OBJECT
public:   
    /*!
     * \brief BaseSimulation constructs a new BaseSimulation
     * \param[in] interfaceUrl URL of the Qt Remote Object simulation interface
     * \param[in] parent a parent object
     */
    BaseSimulation(const QString& interfaceUrl, QObject *parent = nullptr);

    /*!
     * \brief ~BaseSimulation destructs the BaseSimulation
     */
    virtual ~BaseSimulation();

    /*!
     * \brief getReplicaInterface returns a pointer to the Qt Remote Object
     *        inteface replica
     */
    const BSIReplicaSP getReplicaInterface() const {return replicaInterface_;}

    /*!
     * \brief getSituationRectDimensions returns dimensions of the SituationScene
     *        of the GUI where the objects may be displayed
     */
    const RectDimensionsType& getSituationRectDimensions();

    /*!
     * \brief readAndMakeWorldPath reads the path from previously created file
     * \param[in] filePath path to the file where the path is stored
     * \return true on success, false otherwise
     *
     * The scaled path is stored in the simulation inner container.
     *
     * This method may be overloaded for a different scaling coefficient or
     * custom processing of the path (i.e. obtaining the path in other means,
     * using custom coordinate system).
     */
    virtual bool readAndMakeWorldPath(const QString filePath);

    /*!
     * \brief readAndMakeWorldFormation reads the formation from previously
     *        created file
     * \param[in] filePath path to the file where the formation is stored
     * \return true on success, false otherwise
     *
     * The scaled formation is stored in the simulation inner container.
     *
     * This method may be overloaded for different scaling coefficient or
     * custom processing of the formation (i.e. obtaining the formation in
     * other means, using different coordinate system)
     */
    virtual bool readAndMakeWorldFormation(const QString filePath);

    /*!
     * \brief computeScaleFactor computes maximum scale factor to display
     *        objects on the screen effectively
     * \return true on success, false otherwise
     *
     * The scale factor is computed by setting together the dimensions of the
     * SituationScene where the objects are displayed and coordinates of
     * the established path. It assures that the path fits the SituationScene.
     *
     * This method may be overloaded for custom computation of the scale
     * factor.
     */
    virtual bool computeScaleFactor();

    /*!
     * \brief getScaleFactor returns previously computed scale factor
     * \return scale factor
     */
    double getScaleFactor() const {return scaleFactor;}

signals:
    /*!
     * \brief interfaceReady emitted when the simulation correctly connects to
     *        the Qt Remote Object simulation interface
     */
    void interfaceReady();

    /*!
     * \brief clearReq may be emitted when SituationScene has to be cleared
     */
    void clearReq();

    /*!
     * \brief situationRectDimensionsReq may be emitted when dimensions of the
     *        SituationScene is needed
     *
     * However, it is advised to use getSituationRectDimensions()
     */
    void situationRectDimensionsReq();

    /*!
     * \brief situationRectDimensionsReady emitted when requested SituationScene
     *        dimensions delivered
     */
    void situationRectDimensionsReady();

    /*!
     * \brief simulationFinished emitted when the simulation is finished
     */
    void simulationFinished();

private slots:
    void interfaceReadyHandler();
    void situationRectDimensionsInfoHandler(const RectDimensionsType rect);
    void checkIfFinished();

    /*!
     * \brief cannotAddObjectHandler handles a situation when the object cannnot
     *        be added to the SituationScene. May be overloaded for custom behavior
     * \param[in] id an identifier of the object
     */
    virtual void cannotAddObjectHandler(const int id);

    /*!
     * \brief cannotDeleteObjectHandler handles a situation when the object cannnot
     *        be deleted from the SituationScene. May be overloaded for custom behavior
     * \param[in] id an identifier of the object
     */
    virtual void cannotDeleteObjectHandler(const int id);

    /*!
     * \brief cannotUpdateObjectPositionHandler handles a situation when the object's
     *        position cannnot be updated at the SituationScene. May be overloaded for
     *        custom behavior
     * \param[in] id an identifier of the object
     */
    virtual void cannotUpdateObjectPositionHandler(const int id);

public slots:
    /*!
     * \brief run callable entry point of the simulation
     */
    virtual void run();

    /*!
     * \brief stop stops the simulation
     */
    virtual void stop();

protected:
    /// holds robots population
    RobotsManager *rManager;

    /// holds established path
    std::list<Point> worldPath;

    /// holds established formation of the robots
    std::vector<Point> worldFormation;

    /// holds computed scale factor
    double scaleFactor;

private:
    BaseSimulation() = delete;

    /*!
     * \brief runSimulation shall be defined by the classes that derive from
     *        BaseSimulation
     *
     * This is the real entry point of the simulation. The initial simulation
     * logic shall be defined in this method. In here all the robots should be
     * added to the manager. In here all the non-robot simulation objects may
     * be added to the SimulationScene. Returning from this method does not
     * indicate simulation is finished - simulation is done only when all
     * the robots finish their job.
     */
    virtual void runSimulation() = 0;

    QTimer             auxiliaryTimer_;
    BSIReplicaSP       replicaInterface_;
    QRemoteObjectNode  replicaInterfaceNode_;
    RectDimensionsType dimensions_ = {500, 500};
};

#endif // BASESIMULATION_H
