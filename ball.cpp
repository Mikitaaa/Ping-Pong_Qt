#include "ball.h"
#include <QGraphicsScene>

#include <QBrush>
#include <QtMath>
#include <QList>


Ball::Ball() : diameter(20), moveSpeed(5), angle(30) {

    setRect(0, 0, diameter, diameter);
    setBrush(Qt::red);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ball::move);
}

void Ball::move()
{
    // Рассчитываем новые координаты мяча в зависимости от его угла движения
    qreal dx = moveSpeed * qCos(qDegreesToRadians(angle));
    qreal dy = -moveSpeed * qSin(qDegreesToRadians(angle));

    // Перемещаем мяч на новые координаты
    setPos(x() + dx, y() + dy);

    // Получаем список объектов, с которыми происходит столкновение
    QList<QGraphicsItem*> collidingItemsList = collidingItems();

    // Проверяем столкновение с каждым объектом из списка
    for (QGraphicsItem* item : collidingItemsList)
        {
            if (item == this) continue; // Пропускаем проверку столкновения с самим собой (сам мяч)

            // Рассчитываем нормаль к поверхности объекта столкновения
            QPointF normal = mapToItem(this, 0, -1) - item->mapToItem(item, 0, 0);

            // Рассчитываем новый угол движения мяча относительно нормали
            qreal newAngle = qAtan2(-dy, dx) - qAtan2(-normal.y(), normal.x());

            // Отражаем угол от нормали
            angle = qRadiansToDegrees(newAngle) + 180;
        }

    // Получаем границы сцены
    QRectF sceneRect = scene()->sceneRect();

    // Если мяч столкнулся с верхней или нижней границей сцены, меняем угол на противоположный
    if (y() <= sceneRect.top() || y() >= sceneRect.bottom() - diameter)
    {
        angle = -angle;
    }

    // Если мяч столкнулся с левой или правой границей сцены, меняем угол на 180 минус текущий угол
    if (x() <= sceneRect.left() || x() >= sceneRect.right() - diameter)
    {
        angle = 180 - angle;
    }
}


//void Ball::move()
//{
//   if(angle < 0) { angle += 2 * M_PI; }
//   if(angle > 2 * M_PI) { angle -= 2 * M_PI;}

//   qreal oldX = x();
//   qreal oldY = y();

//   setPos(x() + moveSpeed * qCos(qDegreesToRadians(angle)), y() + moveSpeed * qSin(qDegreesToRadians(angle)));

//   QList<QGraphicsItem *> collisions = collidingItems();

//}




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
