#ifndef PLAYER_H
#define PLAYER_H

#include<QGraphicsRectItem>
#include <QGraphicsScene>
#include <QKeyEvent>

class Player : public QGraphicsRectItem
{
public:
    Player();

    void setSize(int width, int height);
    int getHeight() const;
    int getWidth() const;

    void setWrapAroundMovement(bool wrapAround);

protected:
    void keyPressEvent(QKeyEvent *event) override;

protected:
    int height;
    int width;
    int moveSpeed;
    bool wrapAroundMovement;

    void movePlayer(qreal direction);
};

#endif // PLAYER_H
