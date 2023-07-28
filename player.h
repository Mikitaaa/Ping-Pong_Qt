#ifndef PLAYER_H
#define PLAYER_H

#include<QGraphicsRectItem>
#include <QKeyEvent>
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

    void setWrapAroundMovement(bool wrapAround);

    void setBall(Ball* ball);

    void printInfo();

    bool isPlayerHoldingBall;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    Ball* ball;

    int height;
    int width;
    int moveSpeed;
    bool wrapAroundMovement;

    void movePlayer(qreal direction);
    void handleBallCollision();
};

#endif // PLAYER_H
