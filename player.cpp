#include "player.h"
#include <QBrush>

Player::Player()
{
    width = 100;
    height = 20;
    setRect(0, 0, width, height);
    setBrush((QBrush)Qt::black);
    moveSpeed = 50;
}

void Player::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
    setRect(0, 0, width, height);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        moveBy(-moveSpeed, 0);
        break;
    case Qt::Key_Right:
        moveBy(moveSpeed, 0);
        break;
    default:
        break;
    }
}

int Player::getHeight() const
{
    return height;
}

int Player::getWidth() const
{
    return width;
}
