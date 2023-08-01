#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QTimer>

#include <QRandomGenerator>

class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball();
    ~Ball() override;

    void setDiameter(qreal diameter);
    qreal getDiameter() const;

    void setMoveSpeed(qreal moveSpeed);

    void setStartAngle();

    void move();

    QTimer* timer;

private:
    qreal diameter;
    qreal moveSpeed;
    qreal angle;    

signals:
    void gameLost();
};

#endif // BALL_H
