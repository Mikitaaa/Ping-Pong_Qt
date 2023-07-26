#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_NewGameButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    Player* player;

    void InitFieldOnScene(int fieldWidth, int fieldHeight);
};
#endif // MAINWINDOW_H
