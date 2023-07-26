#ifndef PLAYER_H
#define PLAYER_H

#include<QGraphicsRectItem>
#include <QKeyEvent>

class Player : public QGraphicsRectItem
{
public:
    Player();

    void setSize(int width, int height);
    int getHeight() const;
    int getWidth() const;

    void keyPressEvent(QKeyEvent *event) override;

protected:
    int height;
    int width;
    int moveSpeed;
};

#endif // PLAYER_H
