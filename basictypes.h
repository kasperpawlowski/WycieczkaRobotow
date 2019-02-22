#ifndef BASICTYPES_H
#define BASICTYPES_H

#include <string>

struct RectDimentionsType
{
    int width;
    int height;
};

struct PositionType
{
    int    x;
    int    y;
    double a;
};

struct DisplayableObjectType
{
    PositionType       pixmapPosition;
    std::string        pixmapFilename;
    RectDimentionsType pixmapDimensions;
};

#endif // BASICTYPES_H
