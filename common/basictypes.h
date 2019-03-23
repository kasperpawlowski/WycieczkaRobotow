#ifndef BASICTYPES_H
#define BASICTYPES_H

#include <QMetaType>
#include <QDataStream>
#include <cmath>
#include "position.h"

/*!
 * \brief The RectDimensionsType struct describes dimensions of a rectangle
 */
struct RectDimensionsType
{
    int width;
    int height;
};

/*!
 * \brief The PositionType struct describes position of an object in a screen plane
 *
 * \param x holds distance to the y axis
 * \param y holds distance to the x axis
 * \param a holds orientation angle (heading), measured from the x axis
 */
struct PositionType
{
    int    x;
    int    y;
    double a;
};

/*!
 * \brief The DisplayableObjectType struct groups all the parameters needed
 *        for a pixmap object to be correctly displayed
 *
 * \param pixmapPosition holds position of an object
 * \param pixmapFilename holds path to the file representing a pixmap
 * \param pixmapDimensions holds desired dimensions of a pixmap
 */
struct DisplayableObjectType
{
    PositionType       pixmapPosition;
    QString            pixmapFilename;
    RectDimensionsType pixmapDimensions;
};

/*!
 * \brief operator * scales the coordinates of Position object by provided scale factor.
 *        Translates the Position object to screen position.
 * \param[in] pos Position object
 * \param[in] sf scale factor
 * \return scaled PositionType object
 */
PositionType operator*(const Position& pos, const double sf);

/*!
 * \brief operator * scales the coordinates of Position object by provided scale factor.
 *        Translates the Position object to screen position.
 * \param[in] sf scale factor
 * \param[in] pos Position object
 * \return scaled PositionType object
 */
PositionType operator*(const double sf, const Position& pos);

/*!
 * \brief operator needed for Qt Remote Object concept to work properly
 */
QDataStream& operator<<(QDataStream& out, const RectDimensionsType& rect);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimensionsType&)
 */
QDataStream& operator>>(QDataStream& stream, RectDimensionsType& rect);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimensionsType&)
 */
QDataStream& operator<<(QDataStream& out, const PositionType& pos);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimensionsType&)
 */
QDataStream& operator>>(QDataStream& stream, PositionType& pos);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimensionsType&)
 */
QDataStream& operator<<(QDataStream& out, const DisplayableObjectType& obj);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimensionsType&)
 */
QDataStream& operator>>(QDataStream& stream, DisplayableObjectType& obj);

// Declare new types for management in meta-object system
Q_DECLARE_METATYPE(RectDimensionsType);
Q_DECLARE_METATYPE(PositionType);
Q_DECLARE_METATYPE(DisplayableObjectType);

#endif // BASICTYPES_H
