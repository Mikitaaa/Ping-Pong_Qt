#include "player.h"
#include <QBrush>

Player::Player()
{
    width = 100;
    height = 20;
    setRect(0, 0, width, height);
    setBrush((QBrush)Qt::black);
    moveSpeed = 5;
}

void Player::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
    setRect(0, 0, width, height);
}

int Player::getHeight() const
{
    return height;
}

int Player::getWidth() const
{
    return width;
}
