#include <cmath>
#include "point.h"

Point::Point() : x_(0.0), y_(0.0)
{

}

Point::Point(const double x, const double y) :
    x_(x), y_(y)
{

}

Point::Point(const Point& point) :
    x_(point.x_), y_(point.y_)
{

}

void Point::setXY(const Point& point)
{
    x_ = point.getX();
    y_ = point.getY();
}

double Point::distanceTo(const Point& other_point)
{
    return sqrt((other_point.getX() - this->getX()) * (other_point.getX() - this->getX()) +
                (other_point.getY() - this->getY()) * (other_point.getY() - this->getY()));
}

Point Point::operator+(const Point& point)
{
    return Point(this->getX() + point.getX(),
                 this->getY() + point.getY());
}

Point Point::operator-(const Point& point)
{
    return Point(this->getX() - point.getX(),
                 this->getY() - point.getY());
}
