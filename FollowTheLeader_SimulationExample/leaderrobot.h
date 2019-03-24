#ifndef LEADERROBOT_H
#define LEADERROBOT_H

#include "twowheelsrobot.h"

/*!
 * \brief The LeaderRobot class derives from TwoWheelsRobot. It knows the path
 *        that has to be travelled and lets the followers know where it currently
 *        is
 *
 * The LeaderRobot contains a radio device that transmits its current position to
 * the followers
 */
class LeaderRobot : public TwoWheelsRobot
{
    Q_OBJECT
public:
    /*!
     * \brief LeaderRobot constructs a new LeaderRobot of provided identifier
     * \param[in] id new robot's identifier
     * \param[in] rep a pointer to the Qt Remote Object inteface replica
     */
    LeaderRobot(const int id, const BSIReplicaSP rep);

    /*!
     * \brief LeaderRobot copy constructor
     * \param robot LeaderRobot to be copied
     */
    LeaderRobot(const LeaderRobot& robot);

    /*!
     * \brief ~LeaderRobot destructs the LeaderRobot
     */
    ~LeaderRobot();

    /*!
     * \brief clone polimorphic copy constructor
     * \return a pointer to the copied LeaderRobot
     */
    BaseRobot* clone() const;

    /*!
     * \brief setPath sets the path to be travelled
     * \param[in] path desired path
     */
    void setPath(std::list<Point> *path);

signals:
    /*!
     * \brief LeaderAtGoal emitted when robot achieves its destination
     */
    void LeaderAtGoal();

private:
    LeaderRobot() = delete;
    void useOnboardEquipment();

    std::list<Point> *path_;
};

#endif // LEADERROBOT_H
