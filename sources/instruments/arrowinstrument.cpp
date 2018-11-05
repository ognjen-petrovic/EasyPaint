/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "arrowinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"
#include "math.h"

#include <QPen>
#include <QPainter>

ArrowInstrument::ArrowInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void ArrowInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        mStartPoint = mEndPoint = event->pos();
        imageArea.setIsPaint(true);
        mImageCopy = *imageArea.getImage();
        makeUndoCommand(imageArea);
    }
}

void ArrowInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mEndPoint = event->pos();
        imageArea.setImage(mImageCopy);
        if(event->buttons() & Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->buttons() & Qt::RightButton)
        {
            paint(imageArea, true);
        }
    }
}

void ArrowInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        imageArea.setImage(mImageCopy);
        if(event->button() == Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->button() == Qt::RightButton)
        {
            paint(imageArea, true);
        }
        imageArea.setIsPaint(false);
    }
}

void ArrowInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QPainter painter(imageArea.getImage());
    painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                        DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    if(isSecondaryColor)
    {
        painter.setBrush(QBrush(DataSingleton::Instance()->getSecondaryColor()));
    }

    if(mStartPoint != mEndPoint)
    {
        QPoint p1,p2,p3,p4,p5,p6;
        int dx = (mEndPoint.x() - mStartPoint.x())/2;
        int dy = (mEndPoint.y() - mStartPoint.y())/2;
        if (abs(dx) > abs(dy))
        {
            p1 = QPoint(mStartPoint.x() + dx, mEndPoint.y());
            p2 = QPoint(p1.x(), mStartPoint.y() + dy);
            p3 = QPoint(mEndPoint.x(), p2.y());
            p4 = QPoint(mEndPoint.x(), p3.y() - 2 * dy);
            p5 = QPoint(p2.x(), p4.y());
            p6 = QPoint(p1.x(), p5.y() - dy);
        }
        else
        {
            p1 = QPoint(mEndPoint.x(), mStartPoint.y() + dy);
            p2 = QPoint(p1.x() - dx, mStartPoint.y() + dy);
            p3 = QPoint(p2.x(), mEndPoint.y());
            p4 = QPoint(p3.x() - 2 * dx , mEndPoint.y());
            p5 = QPoint(p4.x(), p2.y());
            p6 = QPoint(p5.x() - dx, p1.y());
        }

        const std::array<const QPoint, 7> points = {
            mStartPoint,p1,p2,p3,p4,p5,p6
        };

        painter.drawPolygon(&points[0], 7);

    }

    imageArea.setEdited(true);
    painter.end();
    imageArea.update();
}
