#include "player.h"
#include "ball.h"

#include <QGraphicsScene>
#include <QBrush>

Player::Player() : width(100), height(20), moveSpeed(50) {

    setRect(0, 0, width, height);
    setBrush((QBrush)Qt::black);

    wrapAroundMovement = false;
    ball = nullptr;
}

void Player::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {

    case Qt::Key_Left:
        movePlayer(-moveSpeed);
        break;

    case Qt::Key_Right:
        movePlayer(moveSpeed);
        break;

    case Qt::Key_Space:
        if (ball && ball->scene() == scene()) {
            ball->timer->start(5);
            ball->setParentItem(nullptr);
            ball = nullptr;
        }

    default:
        break;
    }
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

    if (ball && ball->scene() == scene()) {
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

void Player::setBall(Ball* ball) { this->ball = ball; }
