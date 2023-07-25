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
    ui->gameField->setScene(scene);
    scene->setSceneRect(0, 0, width()-30, height()-30);


    int fieldWidth = 600;
    int fieldHeight = 400;

    field = new QGraphicsRectItem(0, 0, fieldWidth, fieldHeight);
    QPen whitePen(Qt::white);
    field->setPen(whitePen);
    scene->addItem(field);

    ui->gameField->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameField->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameField->setGeometry(0, 0, width(), height());
    ui->gameField->setFixedSize(width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}
