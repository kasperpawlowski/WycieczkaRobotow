#ifndef BASESIMULATION_H
#define BASESIMULATION_H

#include <QTimer>
#include "commoninterfaceuser.h"
#include "basictypes.h"
#include "robotsmanager.h"

/*!
 * \brief The BaseSimulation class is an abstract simulation class that has an
 *        access to the GUI and manages simulation. Contains RobotsManager that
 *        takes care of separate robots' threads
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
    const BSIReplicaSP        getReplicaInterface() const {return replicaInterface_;}

    /*!
     * \brief getSituationRectDimensions returns dimensions of the SituationScene
     *        of the GUI where the objects may be displayed
     */
    const RectDimentionsType& getSituationRectDimensions();

signals:
    /*!
     * \brief interfaceReady emitted when the simulation correctly connects to
     *        the Qt Remote Object simulation interface
     */
    void interfaceReady();

    /*!
     * \brief clearReq may be emitted by the user when SituationScene has to be cleared
     */
    void clearReq();

    /*!
     * \brief situationRectDimensionsReq may be emitted by the user when dimensions
     *        of the SituationScene is needed
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
    void situationRectDimensionsInfoHandler(const RectDimentionsType rect);
    void checkIfFinished();
    virtual void cannotAddObjectHandler(const int id);
    virtual void cannotDeleteObjectHandler(const int id);
    virtual void cannotUpdateObjectPositionHandler(const int id);

public slots:
    /*!
     * \brief run callable entry point of the simulation
     */
    void run();

    /*!
     * \brief stop stops the simulation
     */
    void stop();

protected:
    RobotsManager      *rManager;

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
     * indicate simulation finish - simulation is finished only when all the
     * robots finish their job.
     */
    virtual void runSimulation() = 0;

    QTimer             auxiliaryTimer_;
    BSIReplicaSP       replicaInterface_;
    QRemoteObjectNode  replicaInterfaceNode_;
    RectDimentionsType dimensions_ = {500, 500};
};

#endif // BASESIMULATION_H
