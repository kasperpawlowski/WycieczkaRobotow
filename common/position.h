#ifndef POSITION_H
#define POSITION_H

#include "point.h"

/*!
 * \brief The Position class describes position of an object in a real wold plane
 *
 * Derives from Point that holds the coordinates.
 */
class Position : public Point
{
public:
    /*!
     * \brief Position constructs a new default Position
     */
    Position();

    /*!
     * \brief Position constructs a new Position from provided coordinates and heading
     * \param[in] x distance to the y axis
     * \param[in] y distance to the x axis
     * \param[in] orientation angle (heading), measured from the x axis
     */
    Position(const double x, const double y, double a);

    /*!
     * \brief Position constructs a new Position from provided Point and heading
     * \param[in] point Point from which the Position will be created
     * \param[in] a orientation angle (heading), measured from the x axis
     */
    Position(const Point& point, double a);

    /*!
     * \brief Position constructs a new Position from existing Position (a copy constructor)
     * \param[in] pos Position to be copied
     */
    Position(const Position& pos);

    /*!
     * \brief setA sets orientation angle (heading)
     * \param[in] a orientation angle (heading), measured from the x axis
     */
    void setA(const double a);

    /*!
     * \brief getA returns orientation angle (heading)
     * \return orientation angle measured from the x axis
     */
    double getA() const {return  a_;}

    /*!
     * \brief getXY returns X and Y coordinates (Point)
     * \return
     */
    Point getXY() const {return *this;}

    /*!
     * \brief headingAbsDiff computes the absolute difference in heading
     *        between two Position objects
     * \param[in] pos another position object
     * \return angle between 0 and 180 degrees
     */
    double headingAbsDiff(const Position& pos);

    /*!
     * \brief operator + adds coordinates of two Positions and returns resultant Position.
     *        May be pervceived as adding two vectors.
     * \param[in] pos Position which coordinates are added to self coordinates
     * \return result of add operation
     */
    Position operator+(const Position& pos);

    /*!
     * \brief operator - subtracts coordinates of two Positions and returns resultant Position.
     *        May be pervceived as substacting two vectors.
     * \param[in] pos Position which coordinates are subtracted from self coordinates
     * \return result of subtraction operation
     */
    Position operator-(const Position& pos);

protected:
    double a_;
};

#endif // POSITION_H
