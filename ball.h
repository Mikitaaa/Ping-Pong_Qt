#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

class Ball : public QGraphicsEllipseItem
{
public:
    Ball();

    void setDiameter(qreal diameter);
    qreal getDiameter() const;

    void setMoveSpeed(qreal moveSpeed);
    qreal getMoveSpeed() const;

    void setAngle(qreal angle);
    qreal getAngle() const;

private:
    qreal diameter;
    qreal moveSpeed;
    qreal angle;
};

#endif // BALL_H
