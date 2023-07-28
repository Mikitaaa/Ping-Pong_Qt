#include "ball.h"
#include <QGraphicsScene>

#include <QBrush>
#include <QtMath>
#include <QList>

Ball::Ball() : diameter(20), moveSpeed(4), angle(30) {

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

    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (QGraphicsItem* item : collidingItemsList) {
        if (item == this) continue;

        QPointF surfaceNormal = mapToItem(this, 0, -1) - item->mapToItem(item, 0, 0);
        surfaceNormal /= qSqrt(surfaceNormal.x() * surfaceNormal.x() + surfaceNormal.y() * surfaceNormal.y());

        qreal dotProduct = dx * surfaceNormal.x() + dy * surfaceNormal.y();
        dx = dx - 2 * dotProduct * surfaceNormal.x();
        dy = dy - 2 * dotProduct * surfaceNormal.y();

        angle = qRadiansToDegrees(qAtan2(-dy, dx));
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

qreal Ball::getMoveSpeed() const { return moveSpeed; }

void Ball::setAngle(qreal angle) { this->angle = angle; }

qreal Ball::getAngle() const { return angle; }
