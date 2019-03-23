#include <cmath>
#include "position.h"

Position::Position() :
    Point(), a_(0.0)
{

}

Position::Position(const double x, const double y, double a) :
    Point(x, y)
{
    setA(a);
}

Position::Position(const Point& point, double a) :
    Point(point)
{
    setA(a);
}

Position::Position(const Position& pos) :
    Point(pos), a_(pos.a_)
{

}

void Position::setA(const double a)
{
    a_ = fmod(a, 360.0);

    // the heading angle should not be less than 0
    if(a_ < 0.0)
    {
        a_ += 360.0;
    }
}

double Position::headingAbsDiff(const Position& pos)
{
    double diff = this->getA() - pos.getA();

    // the absolute heading difference should be between
    // 0 and 180 degrees
    if(diff < 0.0)
    {
        diff += 360.0;
    }

    if(diff > 180.0)
    {
        diff = 360.0 - diff;
    }

    return diff;
}

Position Position::operator+(const Position& pos)
{
    return Position(this->getX() + pos.getX(),
                    this->getY() + pos.getY(),
                    this->getA() + pos.getA());
}

Position Position::operator-(const Position& pos)
{
    return Position(this->getX() - pos.getX(),
                    this->getY() - pos.getY(),
                    this->getA() - pos.getA());
}
