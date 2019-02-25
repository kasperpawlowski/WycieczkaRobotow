#ifndef BASICTYPES_H
#define BASICTYPES_H

#include <string>

/*!
 * \brief The RectDimentionsType struct describes dimensions of a rectangle
 */
struct RectDimentionsType
{
    int width;
    int height;
};

/*!
 * \brief The PositionType struct describes position of an object in a plane
 *
 * \param x holds distance to the y axis
 * \param y holds distance to the x axis
 * \param a holds orientation angle
 */
struct PositionType
{
    int    x;
    int    y;
    double a;
};

/*!
 * \brief The DisplayableObjectType struct groups all the parameters needed for
 *        a pixmap object to be correctly displayed
 *
 * \param pixmapPosition holds position of an object
 * \param pixmapFilename holds path to the file representing a pixmap
 * \param pixmapDimensions holds desired dimensions of a pixmap
 */
struct DisplayableObjectType
{
    PositionType       pixmapPosition;
    std::string        pixmapFilename;
    RectDimentionsType pixmapDimensions;
};

#endif // BASICTYPES_H
