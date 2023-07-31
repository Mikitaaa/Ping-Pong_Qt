#ifndef PLAYER_H
#define PLAYER_H

#include<QGraphicsRectItem>
#include <QObject>

#include "ball.h"

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player();

    void setSize(int width, int height);
    int getHeight() const;
    int getWidth() const;
    int getmoveSpeed() const;

    void setWrapAroundMovement(bool wrapAround);

    void setBall(Ball* ball);

    void movePlayer(qreal direction);

    bool isPlayerHoldingBall;

protected:
    Ball* ball;

    int height;
    int width;
    int moveSpeed;
    bool wrapAroundMovement;
};

#endif // PLAYER_H
