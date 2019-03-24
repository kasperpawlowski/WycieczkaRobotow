#ifndef FOLLOWERROBOT_H
#define FOLLOWERROBOT_H

#include "twowheelsrobot.h"

/*!
 * \brief The FollowerRobot class derives from TwoWheelsRobot. It knows its own
 *        position, leader position and leader relative position. Taking that into
 *        account, it is able to  compute its desired position so it knows where to
 *        go
 *
 * The FollowerRobot contains a radio device that receives current position of the
 * leader.
 */
class FollowerRobot : public TwoWheelsRobot
{
    Q_OBJECT
public:
    /*!
     * \brief FollowerRobot constructs a new FollowerRobot of provided identifier
     * \param[in] id new robot's identifier
     * \param[in] rep a pointer to the Qt Remote Object inteface replica
     */
    FollowerRobot(const int id, const BSIReplicaSP rep);

    /*!
     * \brief FollowerRobot copy constructor
     * \param robot FollowerRobot to be copied
     */
    FollowerRobot(const FollowerRobot& robot);

    /*!
     * \brief ~FollowerRobot destructs the FollowerRobot
     */
    ~FollowerRobot();

    /*!
     * \brief clone polimorphic copy contructor
     * \return a pointer to the copied FollowerRobot
     */
    BaseRobot* clone() const;

    /*!
     * \brief setLeaderRelativePos sets the leader relative position
     * \param[in] pos leader relative position
     */
    void setLeaderRelativePos(const Position pos) {leaderRelativePos_ = pos;}

    /*!
     * \brief getLeaderRelativePos returns the leader relative position
     * \return
     */
    Position getLeaderRelativePos() const {return leaderRelativePos_;}

    /*!
     * \brief getLeaderRelativeRotatedPos computes the leader relative position
     *        when the leader rotates by rot_angle_deg degrees from original
     *        heading (the one assumed when calling setLeaderRelativePos() )
     * \param[in] rot_angle_deg leader's rotation
     * \return rotated leader relative position
     */
    Position getLeaderRelativeRotatedPos(const double rot_angle_deg) const;

public slots:
    /*!
     * \brief LeaderAtGoalHandler lets the robot know that the leader finished
     *        its role
     */
    void LeaderAtGoalHandler();

private:
    FollowerRobot() = delete;
    void useOnboardEquipment();

    bool     leaderAtGoal_;
    Position fromRadioPos_;
    Position leaderRelativePos_;
};

#endif // FOLLOWERROBOT_H
