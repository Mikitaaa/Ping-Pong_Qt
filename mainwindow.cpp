#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    setFocus();
    countdownSeconds = 10;
    ui->timerLabel->setText(QString::number(countdownSeconds));

    scene = new QGraphicsScene(this);

    int fieldWidth = 700;
    int fieldHeight = 500;
    InitFieldOnScene(fieldWidth, fieldHeight);

    player = new Player();
    player->setPos((fieldWidth - player->getWidth()) / 2, fieldHeight - player->getHeight() - 10);


    ball = new Ball();
    ball->setPos(player->x() + (player->getWidth() - ball->getDiameter()) / 2, player->y() - ball->getDiameter() - 5);
    connect(ball, &Ball::gameLost, this, &MainWindow::GameLoss);
    player->setBall(ball);
    player->isPlayerHoldingBall = true;

    scene->addItem(ball);
    scene->addItem(player);

    ui->gameField->setScene(scene);

     lossGameTimer.setInterval(1000);

    connect(ui->movementModeCheckBox, &QCheckBox::stateChanged, this, &MainWindow::on_movementModeCheckBox_stateChanged);
    connect(&lossGameTimer, &QTimer::timeout, this, &MainWindow::updateTimerLabel);
    lossGameTimer.start();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left:
            player->movePlayer(-player->getmoveSpeed());
            break;

        case Qt::Key_Right:
            player->movePlayer(player->getmoveSpeed());
            break;

        case Qt::Key_Space:
            if (ball && ball->scene() == scene) {
                ball->timer->start(10);
                player->isPlayerHoldingBall = false;
            }
            break;

        default:
            QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::updateTimerLabel() {
    ui->timerLabel->setText(QString::number(countdownSeconds));
    countdownSeconds--;

    // TODO add timeout message
    if (countdownSeconds < 0) {
        lossGameTimer.stop();
        GameLoss();
    }
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

    setFocus();

    QMainWindow::mousePressEvent(event);

}

void MainWindow::on_movementModeCheckBox_stateChanged(int state) {
    player->setWrapAroundMovement(state == Qt::Checked);
}

void MainWindow::GameLoss() {
    on_NewGameButton_clicked();
}

void MainWindow::on_NewGameButton_clicked() {

    countdownSeconds = 10;
    ui->timerLabel->setText(QString::number(countdownSeconds));

    ball->timer->stop();

    player->setPos((ui->gameField->width() - player->getWidth()) / 2, ui->gameField->height() - player->getHeight() - 10);

    ball->setPos(player->x() + (player->getWidth() - ball->getDiameter()) / 2, player->y() - ball->getDiameter() - 5);
    player->isPlayerHoldingBall = true;

    ball->setStartAngle();
}

