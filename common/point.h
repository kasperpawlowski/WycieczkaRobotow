#ifndef POINT_H
#define POINT_H

/*!
 * \brief The Point class describes point coordinates in a real world plane
 */
class Point
{
public:
    /*!
     * \brief Point constructs a new defualt Point
     */
    Point();

    /*!
     * \brief Point constructs a new Point from provided coordinates
     * \param[in] x distance to the y axis
     * \param[in] y distance to the x axis
     */
    Point(const double x, const double y);

    /*!
     * \brief Point constructs a new Point from existing Point (a copy constructor)
     * \param[in] point Point to be copied
     */
    Point(const Point& point);

    /*!
     * \brief setX sets distance to the y axis
     * \param x
     */
    void setX(const double x) {x_ = x;}

    /*!
     * \brief setY sets distance to the x axis
     * \param y
     */
    void setY(const double y) {y_ = y;}

    /*!
     * \brief setXY sets both coordinates of the Point by copying another Point
     *        coordinates
     * \param point
     */
    void setXY(const Point& point);

    /*!
     * \brief getX returns distance to the y axis
     * \return
     */
    double getX() const {return x_;}

    /*!
     * \brief getY returns distance to the x axis
     * \return
     */
    double getY() const {return y_;}

    /*!
     * \brief distanceTo computes distance to another Point
     * \param[in] other_point another Point to which distance is computed
     * \return distance between self and another point
     */
    double distanceTo(const Point& other_point);

    /*!
     * \brief operator + adds coordinates of two Points and returns resultant Point.
     *        May be pervceived as adding two vectors.
     * \param[in] point Point which coordinates are added to self coordinates
     * \return result of add operation
     */
    Point operator+(const Point& point);

    /*!
     * \brief operator - subtracts coordinates of two Points and returns resultant Point.
     *        May be pervceived as substacting two vectors.
     * \param[in] point Point which coordinates are subtracted from self coordinates
     * \return result of subtraction operation
     */
    Point operator-(const Point& point);

protected:
    double x_;
    double y_;
};

#endif // POINT_H
