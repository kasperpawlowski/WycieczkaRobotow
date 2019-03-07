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
     * \brief CommonInterfaceUser constructs a new unconnected CommonInterfaceUser
     */
    CommonInterfaceUser();

    /*!
     * \brief CommonInterfaceUser constructs a new CommonInterfaceUser connected to
     *        the provided Qt Remote Object simulation interface replica
     * \param[in] rep a pointer to the Qt Remote Object inteface replica
     */
    CommonInterfaceUser(const BSIReplicaSP rep);

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
     * \brief isConnectedToTheInterface checks whether the object is properly
     *        connected to the interface
     * \return true when properly connected, false otherwise
     */
    bool isConnectedToTheInterface() const;

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

private:
    bool         connected_;
    BSIReplicaSP replicaInterface_;
};

#endif // COMMONINTERFACEUSER_H
