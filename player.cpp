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
        move(-1);
        break;
    case Qt::Key_Right:
        move(1);
        break;
    default:
        break;
    }
}

void Player::move(int direction)
{
   QPointF currentPos = pos();
   setPos(currentPos.x() + moveSpeed * direction, currentPos.y());
}

int Player::getHeight() const
{
    return height;
}

int Player::getWidth() const
{
    return width;
}
