#include "basictypes.h"

PositionType operator*(const Position& pos, const double sf)
{
    return PositionType({int(round(pos.getX() * sf)), int(round(pos.getY() * sf)), pos.getA()});
}

PositionType operator*(const double sf, const Position& pos)
{
    return pos * sf;
}

QDataStream& operator<<(QDataStream& out, const RectDimensionsType& rect)
{
    out << rect.width << rect.height;
    return out;
}

QDataStream& operator>>(QDataStream& in, RectDimensionsType& rect)
{
    in >> rect.width >> rect.height;
    return in;
}

QDataStream& operator<<(QDataStream& out, const PositionType& pos)
{
    out << pos.x << pos.y << pos.a;
    return out;
}

QDataStream& operator>>(QDataStream& in, PositionType& pos)
{
    in >> pos.x >> pos.y >> pos.a;
    return in;
}

QDataStream& operator<<(QDataStream& out, const DisplayableObjectType& obj)
{
    out << obj.pixmapPosition << obj.pixmapFilename << obj.pixmapDimensions;
    return out;
}

QDataStream& operator>>(QDataStream& in, DisplayableObjectType& obj)
{
    in >> obj.pixmapPosition >> obj.pixmapFilename >> obj.pixmapDimensions;
    return in;
}
