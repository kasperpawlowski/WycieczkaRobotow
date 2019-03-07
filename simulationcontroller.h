#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include <QProcess>
#include "situationscene.h"
#include "simulationinterface.h"

/*!
 * \brief The SimulationController class starts and stops a custom simulation
 *
 * Call startSimulation() to start simulation (a scene on which the simulation
 * objects will be displayed must be provided) or stopSimulation() to stop it.
 * When simulation started, an interface based on Qt Remote Object is created
 * and hosted so the custom simulation can interact with GUI.
 */
class SimulationController : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief SimulationController constructs a new SimulationController
     * \param[in] parent a parent object
     */
    SimulationController(QObject *parent = nullptr);

    /*!
     * \brief ~SimulationController destructs the SimulationController
     */
    ~SimulationController() {}

    /*!
     * \brief setInterfaceURL sets the URL of the Qt Remote Object simulation interface
     */
    void setInterfaceURL(QString url) {interfaceUrl_ = url;}

    /*!
     * \brief setSimulationFilePath sets the path of a custom simulation executable
     */
    void setSimulationFilePath(QString path) {simulationFilePath_ = path;}

    /*!
     * \brief getInterfaceURL returns the URL of the Qt Remote Object simulation interface
     */
    const QString& getInterfaceURL() const {return interfaceUrl_;}

    /*!
     * \brief getSimulationFilePath returns the path of a custom simulation executable
     */
    const QString& getSimulationFilePath() const {return simulationFilePath_;}

public slots:
    /*!
     * \brief startSimulation starts simulation
     * \param[in] situation the scene where the objects will be displayed on
     */
    void startSimulation(const SituationScene *situation);

    /*!
     * \brief stopSimulation stops simulation
     */
    void stopSimulation();

private:
    SimulationInterface *interface_;
    QRemoteObjectHost   *interfaceNode_;
    QProcess            *simulation_;
    QString             interfaceUrl_;
    QString             simulationFilePath_;
};

#endif // SIMULATIONCONTROLLER_H
