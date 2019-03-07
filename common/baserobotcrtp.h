#ifndef BASEROBOTCRTP_H
#define BASEROBOTCRTP_H

#include "baserobot.h"

/*!
 * \brief The BaseRobotCRTP class is a template class based on Curiously
 *        Recurring Template Patern that may be perceived as BaseRobot
 *        wrapper. BaseRobotCRTP releases BaseRobot derived classes
 *        from clone() method definition
 */
template<typename DerivedRobot>
class BaseRobotCRTP : public BaseRobot
{
public:
    BaseRobotCRTP(const int id) : BaseRobot(id) {}

    BaseRobotCRTP(const int id, const PositionType pos, const QString pixmap,
                  const RectDimentionsType dim, const BSIReplicaSP rep) :
        BaseRobot(id, pos, pixmap, dim, rep) {}

    BaseRobotCRTP(const BaseRobotCRTP& robot) : BaseRobot(robot) {}

    BaseRobot* clone() const
    {
        return new DerivedRobot(dynamic_cast<const DerivedRobot&>(*this));
    }
};

#endif // BASEROBOTCRTP_H
