#include <QPainter>
#include <QDebug>
#include "scratchpad.h"

Scratchpad::Scratchpad(QWidget *parent) :
    QWidget(parent), color_(Qt::blue), thickness_(3), alreadyDrawn_(false)
{
    if(!parent)
    {
        qCritical() << "Scratchpad: parent cannot be nullptr";
        return;
    }

    setAttribute(Qt::WA_OpaquePaintEvent);
    image_ = QImage(parent->size(), QImage::Format_RGB32);
    clearScratchpad();
}

bool Scratchpad::isDrawingValid() const
{
    if(!alreadyDrawn_)
    {
        qWarning() << "Scratchpad: there is nothing drawn yet";
        return  false;
    }
    return true;
}

void Scratchpad::clearScratchpad()
{
    alreadyDrawn_ = false;
    pathData_.clear();
    image_.fill(Qt::white);
    update();
}

bool Scratchpad::generatePathData() const
{
    return true;
}

void Scratchpad::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image_);
}

void Scratchpad::mousePressEvent(QMouseEvent *event)
{
    if((event->button() == Qt::LeftButton) && !alreadyDrawn_)
    {
        lastPosition_ = event->pos();
        addPointToPathData(event->pos());
    }
}

void Scratchpad::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && !alreadyDrawn_)
    {
        QPainter painter(&image_);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(color_, thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPosition_, event->pos());

        // for better performance update only the related part of the widget
        int r = painter.pen().width() / 2;
        const QRect rect = QRect(lastPosition_, event->pos()).normalized().adjusted(-r, -r, +r, +r);
        update(rect);

        lastPosition_ = event->pos();
        addPointToPathData(event->pos());
    }
}

void Scratchpad::mouseReleaseEvent(QMouseEvent *event)
{
    if((event->button() == Qt::LeftButton) && !alreadyDrawn_)
    {
        if(pathData_.size() > 1)
        {
            alreadyDrawn_ = true;
            emit mouseCorrectReleaseEvent();
        }
        else
        {
            // clear the scrathpad if only one point has been recorded - it's not a path
            clearScratchpad();
        }
    }
}

void Scratchpad::addPointToPathData(QPoint point)
{
    // translate the position of an event so that the coordinate system begins
    // in the left bottom corner of the widget
    pathData_.push_back(QPoint(point.x(), -point.y() + rect().height()));
}
