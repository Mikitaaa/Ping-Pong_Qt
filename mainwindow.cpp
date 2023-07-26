#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QGraphicsRectItem>
#include <QPen>
#include <QDebug>

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

    scene->addItem(field);
    scene->addItem(player);
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
    ui->gameField->setScene(scene);
    scene->setSceneRect(0, 0, width()-20, height()-20);

    field = new QGraphicsRectItem(0, 0, fieldWidth, fieldHeight);

    field->setBrush(QColor(173, 216, 230));

    QPen whitePen(Qt::black);
    field->setPen(whitePen);

    ui->gameField->setBackgroundBrush(QColor(90, 96, 102));
    ui->gameField->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameField->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameField->setGeometry(0, 0, width(), height());
    ui->gameField->setFixedSize(width(), height());
}


