#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include <QThread>
#include "situationscene.h"

/*!
 * \brief The SimulationController class is a separate thread that starts and
 *        stops simulation
 *
 * Call startSimulation() to start simulation (a scene on which the simulation
 * objects will be displayed must be provided) or stopSimulation() to stop it.
 * When simulation started, an interface based on Qt Remote Object is created
 * and hosted so the custom simulation can interact with GUI.
 */
class SimulationController : public QThread
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
    ~SimulationController() override {}

public slots:
    /*!
     * \brief startSimulation starts simulation
     * \param[in] situation the scene where the objects will be displayed on
     */
    void startSimulation(const SituationScene *const situation);

    /*!
     * \brief stopSimulation stops simulation
     */
    void stopSimulation();

private:
    void run() override;
    const SituationScene* situation_;
};

#endif // SIMULATIONCONTROLLER_H
