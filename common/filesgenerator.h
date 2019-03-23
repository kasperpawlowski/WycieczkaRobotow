#ifndef FILESGENERATOR_H
#define FILESGENERATOR_H

#include <QString>
#include <QPoint>
#include <QFile>
#include <QTextStream>

/*!
 * \brief The FilesGenerator class generates files of desired filename based on
 *        provided Container of QPoints. The class is also able to read the data
 *        from generated file and return a Container of QPoints.
 */
template<template<typename, typename = std::allocator<QPoint>> class Container>
class FilesGenerator
{
public:
    /*!
     * \brief FilesGenerator constructs a new FilesGenerator
     * \param[in] filePath a path to the to be crated file
     */
    FilesGenerator(const QString filePath);

    /*!
     * \brief ~FilesGenerator destructs the FilesGenerator
     */
    virtual ~FilesGenerator();

    /*!
     * \brief generateFile generates the file from a Container of QPoints
     * \param[in] points a Container of QPoints
     * \return true on success, false otherwise
     */
    virtual bool generateFile(const Container<QPoint>& points) const;

    /*!
     * \brief readFromFile reads data from file and returns a Container of
     *        QPoints
     * \return a Container of QPoints created from the file data
     */
    virtual Container<QPoint>& readFromFile();

    /*!
     * \brief generateFile generates the file from a Container of QPoints
     * \param[in] filePath a path to the to be crated file
     * \param[in] points a Container of QPoints
     * \return true on success, false otherwise
     */
    static bool generateFile(const QString filePath, const Container<QPoint>& points);

    /*!
     * \brief readFromFile reads data from file and returns a Container of
     *        QPoints
     * \param[in] filePath a path to the to be crated file
     * \return a Container of QPoints created from the file data
     */
    static Container<QPoint> readFromFile(const QString filePath);

protected:
    FilesGenerator() = delete;
    const QString     filePath_;
    Container<QPoint> points_;
};

template<template<typename, typename = std::allocator<QPoint>> class Container>
FilesGenerator<Container>::FilesGenerator(const QString filePath) :
    filePath_(filePath)
{

}

template<template<typename, typename = std::allocator<QPoint>> class Container>
FilesGenerator<Container>::~FilesGenerator()
{

}

template<template<typename, typename = std::allocator<QPoint>> class Container>
bool FilesGenerator<Container>::generateFile(const Container<QPoint>& points) const
{
    QFile file(filePath_);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return  false;
    }

    QTextStream stream(&file);
    for(typename Container<QPoint>::const_iterator it = points.begin(); it != points.end(); ++it)
    {
        stream << "(" << it->x() << "," << it->y() << ")" << endl;
    }

    file.close();
    return true;
}

template<template<typename, typename = std::allocator<QPoint>> class Container>
Container<QPoint>& FilesGenerator<Container>::readFromFile()
{
    points_.clear();

    QFile file(filePath_);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return points_;
    }

    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        QStringList coordinates = stream.readLine().remove('(').remove(')').split(",");

        if(coordinates.size() == 2)
        {
            bool xOK, yOK;
            int x = coordinates.at(0).toInt(&xOK);
            int y = coordinates.at(1).toInt(&yOK);

            if(xOK && yOK)
            {
                points_.push_back(QPoint(x, y));
            }
        }
    }

    file.close();
    return points_;
}

template<template<typename, typename = std::allocator<QPoint>> class Container>
bool FilesGenerator<Container>::generateFile(const QString filePath, const Container<QPoint>& points)
{
    FilesGenerator<Container> generator(filePath);
    return generator.generateFile(points);
}

template<template<typename, typename = std::allocator<QPoint>> class Container>
Container<QPoint> FilesGenerator<Container>::readFromFile(const QString filePath)
{
    FilesGenerator<Container> generator(filePath);
    return generator.readFromFile();
}

#endif // FILESGENERATOR_H
