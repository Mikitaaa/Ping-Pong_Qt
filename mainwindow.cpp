#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    int fieldWidth = 700;
    int fieldHeight = 500;
    InitFieldOnScene(fieldWidth, fieldHeight);

    player = new Player();
    player->setPos((fieldWidth - player->getWidth()) / 2, fieldHeight - player->getHeight() - 10);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    ball = new Ball();
    ball->setPos(player->x() + (player->getWidth() - ball->getDiameter()) / 2, player->y() - ball->getDiameter() - 5);
    connect(ball, &Ball::gameLost, this, &MainWindow::GameLoss);
    player->setBall(ball);

    scene->addItem(ball);
    scene->addItem(player);

    ui->gameField->setScene(scene);

    connect(ui->movementModeCheckBox, &QCheckBox::stateChanged, this, &MainWindow::on_movementModeCheckBox_stateChanged);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_NewGameButton_clicked()
{

}

void MainWindow::InitFieldOnScene(int fieldWidth, int fieldHeight) {
    scene->setSceneRect(10, 10, fieldWidth, fieldHeight);

    ui->gameField->setBackgroundBrush(QColor(90, 96, 102));

    ui->gameField->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameField->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->gameField->setGeometry(10, 10, fieldWidth, fieldHeight);
    ui->gameField->setFixedSize(fieldWidth, fieldHeight);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    if (player) { player->setFocus(); }

    QMainWindow::mousePressEvent(event);

}

void MainWindow::on_movementModeCheckBox_stateChanged(int state) {
    player->setWrapAroundMovement(state == Qt::Checked);
}

void MainWindow::GameLoss() {
    ball->timer->stop();

    player->setPos((ui->gameField->width() - player->getWidth()) / 2, ui->gameField->height() - player->getHeight() - 10);

    ball->setPos(player->x() + (player->getWidth() - ball->getDiameter()) / 2, player->y() - ball->getDiameter() - 5);

    player->setBall(ball);
}
