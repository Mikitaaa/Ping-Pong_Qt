#include "mainwindow.h"

#include <QGridLayout>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), level(1) {
    setFocusPolicy(Qt::StrongFocus);
    countdownSeconds = 10;

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    scene = new QGraphicsScene(this);
    gameField = new QGraphicsView(scene, centralWidget);

    int fieldWidth = 700;
    int fieldHeight = 500;
    InitFieldOnScene(fieldWidth, fieldHeight);

    timerLabel = new QLabel(QString::number(countdownSeconds), centralWidget);
    newGameButton = new QPushButton("New Game", centralWidget);
    movementModeCheckBox = new QCheckBox("Looped move", centralWidget);
    setupTimerLable();

    QGridLayout *mainLayout = new QGridLayout(centralWidget);
    mainLayout->addWidget(gameField, 0, 0, 4, 1);
    mainLayout->addWidget(newGameButton, 1, 1);
    mainLayout->addWidget(movementModeCheckBox, 2, 1);
    mainLayout->addWidget(timerLabel, 0, 1, 1, 1);

    player = new Player();
    player->setPos((fieldWidth - player->getWidth()) / 2, fieldHeight - player->getHeight() - 10);

    ball = new Ball();
    ball->setPos(player->x() + (player->getWidth() - ball->getDiameter()) / 2, player->y() - ball->getDiameter() - 5);
    connect(ball, &Ball::gameLost, this, &MainWindow::GameLoss);

    player->setBall(ball);
    player->isPlayerHoldingBall = true;

    scene->addItem(ball);
    scene->addItem(player);

    connect(newGameButton, &QPushButton::clicked, this, &MainWindow::on_NewGameButton_clicked);
    connect(movementModeCheckBox, &QCheckBox::stateChanged, this, &MainWindow::on_movementModeCheckBox_stateChanged);
    connect(&WinGameTimer, &QTimer::timeout, this, &MainWindow::updateTimerLabel);
    WinGameTimer.setInterval(1000);

}

MainWindow::~MainWindow() { delete scene; }

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
                if (!ball->timer->isActive()) {ball->timer->start(10); }
                player->isPlayerHoldingBall = false;
                if (!WinGameTimer.isActive()) {WinGameTimer.start(); }
            }
            break;

        default:
            QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::updateTimerLabel() {
    countdownSeconds--;
    timerLabel->setText(QString::number(countdownSeconds));

    if (countdownSeconds < 0) {
        WinGameTimer.stop();
        GameWin();
    }
}

void MainWindow::GameLoss() {
    // TODO game loss message
    on_NewGameButton_clicked();
}

void MainWindow::GameWin() {
    // TODO game win message

    // функцию setRandomBlocks
    // которая принимает количество блоков
    // она выставляет это количество блоков в случайном порядке
    // под случайным углом,блоки не могут быть расположены ниже игрока и за картой
    // можно создать массив, хранящий все возможные варианты блоков, и ставиться будут случайные из массива,
    // создать усложнение уровней за счет увеличения количества блоков, до определенного уровня, после которого
    // сложность начет меняться например за счет увеличения скорости мяча, уменьшения скорости игрока
    on_NewGameButton_clicked();
}

void MainWindow::on_NewGameButton_clicked() {
    if (WinGameTimer.isActive()) { WinGameTimer.stop(); }

    countdownSeconds = 10;
    timerLabel->setText(QString::number(countdownSeconds));

    ball->timer->stop();

    player->setPos((gameField->width() - player->getWidth()) / 2, gameField->height() - player->getHeight() - 10);

    ball->setPos(player->x() + (player->getWidth() - ball->getDiameter()) / 2, player->y() - ball->getDiameter() - 5);
    player->isPlayerHoldingBall = true;

    ball->setStartAngle();

    setRandomBlocks(level);
}

void MainWindow::setRandomBlocks(int lvl) {
    QGraphicsRectItem *newBlock = new QGraphicsRectItem();
    newBlock->setRect(0, 0, 100, 100);
    newBlock->setBrush((QBrush)Qt::black);
    scene->addItem(newBlock);
}

void MainWindow::InitFieldOnScene(int fieldWidth, int fieldHeight) {
    scene->setSceneRect(10, 10, fieldWidth, fieldHeight);

    scene->setBackgroundBrush(QColor(90, 96, 102));

    gameField->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameField->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gameField->setGeometry(10, 10, fieldWidth, fieldHeight);
    gameField->setFixedSize(fieldWidth, fieldHeight);
    gameField->setFocusPolicy(Qt::NoFocus);
}

void MainWindow::setupTimerLable() {
    timerLabel->setFixedSize(100, 50);
    QFont font("Arial", 20);
    timerLabel->setFont(font);
    timerLabel->setStyleSheet("background-color: black;");

    timerLabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_movementModeCheckBox_stateChanged(int state) {
    player->setWrapAroundMovement(state == Qt::Checked);
}

