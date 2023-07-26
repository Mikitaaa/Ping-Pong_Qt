#include "ball.h"
#include <QBrush>


Ball::Ball()
    : diameter(20), moveSpeed(5), angle(0)
{
    setRect(0, 0, diameter, diameter);
    setBrush(Qt::red);
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
