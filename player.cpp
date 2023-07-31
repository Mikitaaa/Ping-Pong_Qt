#include "player.h"

#include <QGraphicsScene>
#include <QBrush>
#include <QtMath>

Player::Player() : width(150), height(10), moveSpeed(50) {

    setRect(0, 0, width, height);
    setBrush((QBrush)Qt::black);

    wrapAroundMovement = false;
    ball = nullptr;
    isPlayerHoldingBall = false;
}

void Player::movePlayer(qreal direction) {
    qreal newX = x() + direction;

    QRectF sceneRect = scene()->sceneRect();
    qreal sceneRight = sceneRect.right();
    qreal sceneLeft = sceneRect.left();

    if (wrapAroundMovement) {
    // if player's pos was out of scene bounds set player pos to the other side of the scene
        if (newX + width < sceneLeft) { newX = sceneRight - width; }
        else if (newX > sceneRight) {  newX = sceneLeft; }

    } else {
    // if player's pos has reached the scene bounds leave player's pos at the bound pos
        if (newX < sceneLeft) { newX = sceneLeft; }
        else if (newX + width > sceneRight) { newX = sceneRight - width; }
    }

    setX(newX);

    if (isPlayerHoldingBall) {
        qreal newBallX = x() + (width - ball->getDiameter()) / 2;
        qreal newBallY = y() - ball->getDiameter() - 5;
        ball->setPos(newBallX, newBallY);
    }
}

void Player::setSize(int width, int height) {

    this->width = width;
    this->height = height;
    setRect(0, 0, width, height);
}

void Player::setWrapAroundMovement(bool wrapAround) {  this->wrapAroundMovement = wrapAround; }

int Player::getHeight() const { return height; }

int Player::getWidth() const { return width; }

int Player::getmoveSpeed() const { return moveSpeed; }

void Player::setBall(Ball* ball) { this->ball = ball; }
