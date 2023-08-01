#include "ball.h"
#include "player.h"
#include <QGraphicsScene>

#include <QBrush>
#include <QtMath>
#include <QList>

Ball::Ball() : diameter(20), moveSpeed(3), angle(135) {

    angle -= QRandomGenerator::global()->generateDouble() * 90;
    setRect(0, 0, diameter, diameter);
    setBrush(Qt::red);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ball::move);
}

void Ball::move() {
    qreal dx = moveSpeed * qCos(qDegreesToRadians(angle));
    qreal dy = -moveSpeed * qSin(qDegreesToRadians(angle));

    qreal newX = x() + dx;
    qreal newY = y() + dy;

    QRectF sceneRect = scene()->sceneRect();
    if (newY >= sceneRect.bottom() - diameter) {
        emit gameLost();
        return;
    }

    setPos(newX, newY);
// handling collisions
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
        for (QGraphicsItem* item : collidingItemsList) {

            if (item == this) continue;

            if (Player* player = dynamic_cast<Player*>(item)) {
                if (this->collidesWithItem(player)) {

                    QPointF collisionPoint = mapToItem(player, 0, 0);
                    qreal collisionVectorX = collisionPoint.x() - diameter / 2;
                    qreal collisionVectorY = collisionPoint.y() - diameter / 2;
                    qreal collisionAngle = qRadiansToDegrees(qAtan2(collisionVectorY, collisionVectorX));

                    // handle right and left collisions with plyer:
                    // with an instant movement of the player
                    // ball may be insidee the player if the ball was lower on scene
                    qreal lowestBallY = y() + diameter/2;
                    qreal highestPlayerY = player->y();

                    if (lowestBallY > highestPlayerY) {
                        qreal ballCenterX = x() + diameter / 2;
                        qreal playerCenterX = player->x() + player->getWidth() / 2;
                        if (ballCenterX > playerCenterX) {
                            setX(player->x() + player->getWidth() + 2);
                            angle = 315;
                            break;
                        }else {
                            setX(player->x() - diameter - 2);
                            angle = 225;
                            break;
                        }
                    }

                    qreal reflectionAngleRange = 150.0;
                    qreal maxDeviation = 30.0;
                    qreal reflectAngle = reflectionAngleRange * (collisionAngle / 90.0);

                    qreal randomDeviation = QRandomGenerator::global()->generateDouble() * maxDeviation - maxDeviation / 2;
                    reflectAngle += randomDeviation;

                    qreal newAngle = qDegreesToRadians(180 + reflectAngle);

                    angle = qRadiansToDegrees(newAngle);
                }
            }
        }

    // Handle collisions with scene borders
    if (newX <= sceneRect.left() || newX >= sceneRect.right() - diameter) {
        dx = -dx;
        angle = qRadiansToDegrees(qAtan2(-dy, dx));
    } else if(newY <= sceneRect.top()) {
        dy = -dy;
        angle = qRadiansToDegrees(qAtan2(-dy, dx));
    }

    setPos(x() + dx, y() + dy);
}

Ball::~Ball() {
    timer->stop();
    delete timer;
}

void Ball::setDiameter(qreal diameter) {
    this->diameter = diameter;
    setRect(0, 0, diameter, diameter);
}

qreal Ball::getDiameter() const { return diameter; }

void Ball::setMoveSpeed(qreal moveSpeed) {  this->moveSpeed = moveSpeed; }

void Ball::setStartAngle() { this->angle = 135 - QRandomGenerator::global()->generateDouble() * 90; }
