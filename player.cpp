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
    qreal newX = x();

    switch (event->key()) {
    case Qt::Key_Left:
        newX -= moveSpeed;
        break;
    case Qt::Key_Right:
        newX += moveSpeed;
        break;
    default:
        break;
    }

    QRectF sceneRect = scene()->sceneRect();
    if (newX >= sceneRect.left() && newX + width <= sceneRect.right()) {
        setX(newX);
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
