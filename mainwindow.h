#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

#include "player.h"
#include "ball.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_NewGameButton_clicked();
    void on_movementModeCheckBox_stateChanged(int state);
    void GameLoss();
    void GameWin();
    void updateTimerLabel();

private:
    QGraphicsScene* scene;
    QGraphicsView *gameField;

    QList<QGraphicsItem*> blockShapes;
    Player* player;
    Ball* ball;

    QLabel* levelLabel;
    QLabel* timerLabel;
    QPushButton* newGameButton;
    QCheckBox* movementModeCheckBox;

    void InitFieldOnScene(int fieldWidth, int fieldHeight);
    void setupLables();

    void initItems();
    void setRandomBlocks(int lvl);
    bool checkCollisions(QGraphicsItem *shape, qreal x, qreal y);

    void newGame();

    QTimer WinGameTimer;
    int countdownSeconds;

    int level;
};

#endif // MAINWINDOW_H
