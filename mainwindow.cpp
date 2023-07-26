#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    int fieldWidth = 700;
    int fieldHeight = 500;
    InitFieldOnScene(fieldWidth, fieldHeight);

    player = new Player();

    player->setPos((fieldWidth - player->getWidth()) / 2, fieldHeight - player->getHeight() - 10);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);

ui->gameField->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NewGameButton_clicked()
{

}

void MainWindow::InitFieldOnScene(int fieldWidth, int fieldHeight)
{
    scene->setSceneRect(10, 10, fieldWidth, fieldHeight);

    ui->gameField->setBackgroundBrush(QColor(90, 96, 102));

    ui->gameField->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameField->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->gameField->setGeometry(10, 10, fieldWidth, fieldHeight);
    ui->gameField->setFixedSize(fieldWidth, fieldHeight);
}


