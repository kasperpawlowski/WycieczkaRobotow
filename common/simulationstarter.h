#ifndef SIMULATIONSTARTER_H
#define SIMULATIONSTARTER_H

#include <QCoreApplication>
#include "basesimulation.h"

/*!
 * \brief The SimulationStarter class is a template class that starts the BaseSimulation
 *        derived simulation (provided as a template parameter)
 *
 * It is used for ease of simulation maintenance.
 */
template<typename BaseSimulationDerived>
class SimulationStarter
{
public:
    /*!
     * \brief SimulationStarter creates a new SimulationStarter
     * \param[in] app pointer to the core application
     * \param[in] interface_url URL of the Qt Remote Object simulation interface
     */
    SimulationStarter(const QCoreApplication *app, const char *interface_url);

    /*!
     * \brief ~SimulationStarter destructs the SimulationStarter
     */
    ~SimulationStarter();

private:
    SimulationStarter() = delete;
    SimulationStarter(const SimulationStarter&) = delete;

    BaseSimulation *simulation_;
};

template<typename BaseSimulationDerived>
SimulationStarter<BaseSimulationDerived>::SimulationStarter(const QCoreApplication *app, const char *interface_url)
{
    simulation_ = dynamic_cast<BaseSimulation*>(new BaseSimulationDerived(interface_url));

    QObject::connect(simulation_, SIGNAL(interfaceReady()),
                     simulation_, SLOT(run()));

    QObject::connect(simulation_, SIGNAL(simulationFinished()),
                     app, SLOT(quit()));

    QObject::connect(app, SIGNAL(aboutToQuit()),
                     simulation_, SLOT(stop()));
}

template<typename BaseSimulationDerived>
SimulationStarter<BaseSimulationDerived>::~SimulationStarter()
{
    delete simulation_;
}

#endif // SIMULATIONSTARTER_H
