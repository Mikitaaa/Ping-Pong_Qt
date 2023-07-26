#include "ball.h"
#include <QGraphicsScene>

#include <QBrush>
#include <QtMath>

Ball::Ball()
    : diameter(20), moveSpeed(5), angle(90)
{
    setRect(0, 0, diameter, diameter);
    setBrush(Qt::red);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ball::move);
}

void Ball::move()
{
    qreal dx = moveSpeed * qCos(qDegreesToRadians(angle));
    qreal dy = -moveSpeed * qSin(qDegreesToRadians(angle));

    setPos(x() + dx, y() + dy);

    QRectF sceneRect = scene()->sceneRect();

    if (y() < sceneRect.top() || y() > sceneRect.bottom() - diameter)
        {
            angle = -angle;
        }

    if (x() <= sceneRect.left() || x() >= sceneRect.right() - diameter)
        {
            angle = 180 - angle;
        }
}

void Ball::setDiameter(qreal diameter)
{
    this->diameter = diameter;
    setRect(0, 0, diameter, diameter);
}

qreal Ball::getDiameter() const
{
    return diameter;
}

void Ball::setMoveSpeed(qreal moveSpeed)
{
    this->moveSpeed = moveSpeed;
}

qreal Ball::getMoveSpeed() const
{
    return moveSpeed;
}

void Ball::setAngle(qreal angle)
{
    this->angle = angle;
}

qreal Ball::getAngle() const
{
    return angle;
}

Ball::~Ball()
{
    timer->stop();
    delete timer;
}
