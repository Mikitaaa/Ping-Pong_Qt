#include "player.h"

#include <QGraphicsScene>
#include <QBrush>
#include <QtMath>

#include <QDebug>

Player::Player() : width(100), height(70), moveSpeed(50) {

    setRect(0, 0, width, height);
    setBrush((QBrush)Qt::black);

    wrapAroundMovement = false;
    ball = nullptr;
    isPlayerHoldingBall = false;
}

void Player::printInfo() {
    qDebug() << "Player: x =" << x() << ", y =" << y() << ", width =" << width << ", height =" << height;
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
            ball->timer->start(20);
           isPlayerHoldingBall = false;
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

    handleBallCollision();

    if (isPlayerHoldingBall) {
        qreal newBallX = x() + (width - ball->getDiameter()) / 2;
        qreal newBallY = y() - ball->getDiameter() - 5;
        ball->setPos(newBallX, newBallY);
    }
}

void Player::handleBallCollision() {

    if (ball && ball->collidesWithItem(this)) {
        qreal playerTopY = y();
        qreal ballBottomY = ball->y() - ball->getDiameter();

        if (ballBottomY < playerTopY) {
            qreal playerCenterX = x() + width / 2;
            qreal ballCenterX = ball->x() + ball->getDiameter() / 2;

            if (playerCenterX >= ballCenterX) {
                ball->setPos(x() - ball->getDiameter() - 1, ball->y());
            } else {
                ball->setPos(x() + width + ball->getDiameter() + 1, ball->y());
            }
        } else {
            // Изменяем угол полета мяча при столкновении с игроком
            qreal playerCenterX = x() + width / 2;
            qreal ballCenterX = ball->x() + ball->getDiameter() / 2;

            // Вычисляем новый угол отражения мяча
            qreal newAngle = 2 * qAtan2(ball->getAngle(), playerCenterX - ballCenterX);
            ball->setAngle(qRadiansToDegrees(newAngle));
        }
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
