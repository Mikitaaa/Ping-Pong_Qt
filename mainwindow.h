#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "player.h"
#include "ball.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void on_NewGameButton_clicked();

    void on_movementModeCheckBox_stateChanged(int state);

    void GameLoss();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    Player* player;
    Ball* ball;

    void InitFieldOnScene(int fieldWidth, int fieldHeight);
};
#endif // MAINWINDOW_H
