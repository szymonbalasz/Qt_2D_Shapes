#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor(112,112,112),
    mPen(Qt::white),
    mShape (Astroid)
{
    mPen.setWidth(3);

    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(600, 600);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 400);
}

void RenderArea::on_shape_changed()
{
    switch (mShape) {
    case Astroid:
        mScale = 90;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;

    case Cycloid:
        mScale = 10;
        mIntervalLength = 4 * M_PI;
        mStepCount = 128;
        break;

    case HuygensCycloid:
        mScale = 12;
        mIntervalLength = 4 * M_PI;
        mStepCount = 256;
        break;

    case HypoCycloid:
        mScale = 40;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;

    case Line:
        mScale = 50;
        mIntervalLength = 2;
        mStepCount = 128;
        break;

    case Circle:
        mScale = 150;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;

    case Ellipse:
        mScale = 75;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;

    case Twirly:
        mScale = 12;
        mIntervalLength = 12 * M_PI;
        mStepCount = 512;
        break;

    case Starfish:
        mScale = 35;
        mIntervalLength = 6 * M_PI;
        mStepCount = 128;
        break;

    case Cloud:
        mScale = 14;
        mIntervalLength = 28 * M_PI;
        mStepCount = 256;
        break;

    default:
        break;
    }
}

QPointF RenderArea::compute(float t)
{
    switch (mShape) {
    case Astroid:
        return compute_astroid(t);
        break;

    case Cycloid:
        return compute_cycloid(t);
        break;

    case HuygensCycloid:
        return compute_huygens(t);
        break;

    case HypoCycloid:
        return compute_hypo(t);
        break;

    case Line:
        return compute_line(t);
        break;

    case Circle:
        return compute_circle(t);
        break;

    case Ellipse:
        return compute_ellipse(t);
        break;

    case Twirly:
        return compute_twirly(t);
        break;

    case Starfish:
        return compute_starfish(t);
        break;

    case Cloud:
        return compute_cloud(t);
        break;


    default:
        break;
    }
    return QPointF (0, 0);
}

QPointF RenderArea::compute_astroid(float t)
{
    float cos_t = cos (t);
    float sin_t = sin (t);
    float x = 2 * cos_t * cos_t * cos_t;
    float y = 2 * sin_t * sin_t * sin_t;
    return QPointF(x, y);
}

QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF (
                (1.5*(1-cos(t))),
                (1.5*(t-sin(t)))
                );
}

QPointF RenderArea::compute_huygens(float t)
{
    return QPointF (
                (4*(3*cos(t) - cos(3*t))),
                (4*(3*sin(t) - sin(3*t))));
}

QPointF RenderArea::compute_hypo(float t)
{
    return QPointF (
                (1.5*(2*cos(t) + cos(2*t))),
                (1.5*(2*sin(t) - sin(2*t)))
                );
}

QPointF RenderArea::compute_line(float t)
{
    return QPointF (1-t, 1-t);
}

QPointF RenderArea::compute_circle(float t)
{
    return QPointF (
                cos(t),
                sin(t)
                );
}

QPointF RenderArea::compute_ellipse(float t)
{
    float a = 2;
    float b = 1;
    return QPointF (
                a * cos(t),
                b * sin(t)
                );
}

QPointF RenderArea::compute_twirly(float t)
{
    float v1 = 11.0f;
    float v2 = 6;

    float x = v1 * cos(t) - 6 * cos((v1 / 6) * t);
    float y = v1 * sin(t) - 6 * sin((v1 / 6) * t);
    return QPointF (x, y);
}

QPointF RenderArea::compute_starfish(float t)
{
    float R = 5;
    float r = 3;
    float d = 5;
    float x = (R - r) * cos(t) + d * cos(t * ((R - r) / r));
    float y = (R - r) * sin(t) - d * sin(t * ((R - r) / r));

    return QPointF (x, y);
}

QPointF RenderArea::compute_cloud(float t)
{
    float a = 14;
    float b = 1;
    float x = (a + b) * cos(t * b/a) - b * cos(t * (a+b)/a);
    float y = (a + b) * sin(t * b/a) - b * sin(t * (a+b)/a);

    return QPointF (x, y);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);


    painter.setBrush(mBackgroundColor);
    painter.setPen(mPen);

    //drawing area
    painter.drawRect(this->rect());


    QPoint center = this->rect().center();
    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX(prevPoint.x() * mScale + center.x());
    prevPixel.setY(prevPoint.y() * mScale + center.y());
    float step = mIntervalLength / mStepCount;
    for (float t = 0; t < mIntervalLength; t+= step) {
        QPointF point = compute(t);

        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());

        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }

    //run function one more time to draw last line segment to complete shape

    QPointF point = compute(mIntervalLength);

    QPoint pixel;
    pixel.setX(point.x() * mScale + center.x());
    pixel.setY(point.y() * mScale + center.y());

    painter.drawLine(pixel, prevPixel);

}

