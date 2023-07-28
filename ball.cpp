#include "ball.h"
#include <QGraphicsScene>

#include <QBrush>
#include <QtMath>
#include <QList>

#include <QDebug>

Ball::Ball() : diameter(20), moveSpeed(7), angle(30) {

    setRect(0, 0, diameter, diameter);
    setBrush(Qt::red);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ball::move);
}

void Ball::printInfo() {
    qDebug() << "Ball: x =" << x() << ", y =" << y() << ", diameter =" << diameter;
}

void Ball::move() {
    qreal dx = moveSpeed * qCos(qDegreesToRadians(angle));
    qreal dy = -moveSpeed * qSin(qDegreesToRadians(angle));

    setPos(x() + dx, y() + dy);

    QList<QGraphicsItem*> collidingItemsList = collidingItems();

    for (QGraphicsItem* item : collidingItemsList)
        {
            if (item == this) continue;

            QPointF SurfaseNormal = mapToItem(this, 0, -1) - item->mapToItem(item, 0, 0);

            qreal newAngle = qAtan2(-dy, dx) - qAtan2(-SurfaseNormal.y(), SurfaseNormal.x());

            angle = qRadiansToDegrees(newAngle) + 180;
        }

    // Borders collisions
    QRectF sceneRect = scene()->sceneRect();

    if (y() <= sceneRect.top()) { angle = -angle; }

    if (y() >= sceneRect.bottom() - diameter) { emit gameLost(); }

    if (x() <= sceneRect.left() || x() >= sceneRect.right() - diameter) {  angle = 180 - angle; }

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
