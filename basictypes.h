#ifndef BASICTYPES_H
#define BASICTYPES_H

#include <QMetaType>
#include <QDataStream>

/*!
 * \brief Describes dimensions of a rectangle
 */
struct RectDimentionsType
{
    int width;
    int height;
};

/*!
 * \brief Describes position of an object in a plane
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
 * \brief Groups all the parameters needed for a pixmap object to be correctly
 *        displayed
 *
 * \param pixmapPosition holds position of an object
 * \param pixmapFilename holds path to the file representing a pixmap
 * \param pixmapDimensions holds desired dimensions of a pixmap
 */
struct DisplayableObjectType
{
    PositionType       pixmapPosition;
    QString            pixmapFilename;
    RectDimentionsType pixmapDimensions;
};

/*!
 * \brief operator needed for Qt Remote Object concept to work properly
 */
QDataStream& operator<<(QDataStream& out, const RectDimentionsType& rect);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimentionsType&)
 */
QDataStream& operator>>(QDataStream& stream, RectDimentionsType& rect);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimentionsType&)
 */
QDataStream& operator<<(QDataStream& out, const PositionType& pos);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimentionsType&)
 */
QDataStream& operator>>(QDataStream& stream, PositionType& pos);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimentionsType&)
 */
QDataStream& operator<<(QDataStream& out, const DisplayableObjectType& obj);

/*!
 * \brief \copydoc operator<<(QDataStream&, const RectDimentionsType&)
 */
QDataStream& operator>>(QDataStream& stream, DisplayableObjectType& obj);

// Declare new types for management in meta-object system
Q_DECLARE_METATYPE(RectDimentionsType);
Q_DECLARE_METATYPE(PositionType);
Q_DECLARE_METATYPE(DisplayableObjectType);

#endif // BASICTYPES_H
