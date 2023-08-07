#include "mainwindow.h"

#include <QGridLayout>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), level(30) {
    setFocusPolicy(Qt::StrongFocus);
    countdownSeconds = 10;

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    scene = new QGraphicsScene(this);
    gameField = new QGraphicsView(scene, centralWidget);

    int fieldWidth = 700;
    int fieldHeight = 500;
    InitFieldOnScene(fieldWidth, fieldHeight);

    levelLabel= new QLabel("level: " + QString::number(level), centralWidget);
    timerLabel = new QLabel(QString::number(countdownSeconds), centralWidget);
    newGameButton = new QPushButton("New Game", centralWidget);
    movementModeCheckBox = new QCheckBox("Looped move", centralWidget);
    setupLables();

    QGridLayout *mainLayout = new QGridLayout(centralWidget);
    mainLayout->addWidget(gameField, 0, 0, 5, 1);
    mainLayout->addWidget(newGameButton, 1, 1);
    mainLayout->addWidget(movementModeCheckBox, 2, 1);
    mainLayout->addWidget(timerLabel, 0, 1, 1, 1);
    mainLayout->addWidget(levelLabel, 3, 1, 1, 1);

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

    initItems();
    setRandomBlocks(level);

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

    if(level > 0) { --level; }

    on_NewGameButton_clicked();
}

void MainWindow::GameWin() {
    // TODO game win message

    // сейчас каждые 10 уровней добавляется блок
    /*
    при достижении 20 уровня на поле будет стоять 10 объектов,
            в начале на каждый новый уровень на сцене будет на 1 объект больше,
            чем было, далее до 20 уровня будет становиться на 1 объект больше каждые 2 уровня,
            после 20 уровня количество объектов увеличиваться не будет
            начнет увеличиваться скорость мяча
     */
    ++level;
    on_NewGameButton_clicked();
}

void MainWindow::on_NewGameButton_clicked() {
    if (WinGameTimer.isActive()) { WinGameTimer.stop(); }

    countdownSeconds = 10;
    timerLabel->setText(QString::number(countdownSeconds));
    levelLabel->setText("level: " + QString::number(level));

    ball->timer->stop();

    player->setPos((gameField->width() - player->getWidth()) / 2, gameField->height() - player->getHeight() - 10);

    ball->setPos(player->x() + (player->getWidth() - ball->getDiameter()) / 2, player->y() - ball->getDiameter() - 5);
    player->isPlayerHoldingBall = true;

    ball->setStartAngle();

    // clear scene from items
    for (QGraphicsItem* item : scene->items()) {
        if (item != player && item != ball) {
            scene->removeItem(item);
        }
    }

    setRandomBlocks(level);
}

void MainWindow::setRandomBlocks(int lvl) {
    int numBlocks = qMin(1 + lvl / 10, 10);

    for (int i = 0; i < numBlocks; ++i) {
        int randomIndex = QRandomGenerator::global()->bounded(blockShapes.size());
        QGraphicsItem* shape = blockShapes[randomIndex];

        while (scene->items().contains(shape)) {
                randomIndex = QRandomGenerator::global()->bounded(blockShapes.size());
                shape = blockShapes[randomIndex];
            }

        int x = QRandomGenerator::global()->bounded(scene->width() - shape->boundingRect().width());
        int y = QRandomGenerator::global()->bounded(scene->height() - shape->boundingRect().height());
        qreal angle = QRandomGenerator::global()->bounded(360.0);

        shape->setPos(x, y);
        shape->setRotation(angle);
        scene->addItem(shape);
    }

}

void MainWindow::initItems() {
    int circleDiameter = 20;
    int rectangleWidth = 30;
    int rectangleHeight = 20;

    //  5 circles
    for (int i = 0; i < 5; ++i) {
        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(0, 0, circleDiameter, circleDiameter);
        circle->setBrush(QBrush(QColor(qrand() % 256, qrand() % 256, qrand() % 256)));
        blockShapes.append(circle);
    }

    //  5 rectangles
    for (int i = 0; i < 5; ++i) {
        QGraphicsRectItem* rectangle = new QGraphicsRectItem(0, 0, rectangleWidth, rectangleHeight);
        rectangle->setBrush(QBrush(QColor(qrand() % 256, qrand() % 256, qrand() % 256)));
        blockShapes.append(rectangle);
    }

    //  5 triangles
    for (int i = 0; i < 5; ++i) {
        QPolygonF triangle;
        triangle << QPointF(0, 0) << QPointF(20, 0) << QPointF(10, 20);
        QGraphicsPolygonItem* polygon = new QGraphicsPolygonItem(triangle);
        polygon->setBrush(QBrush(QColor(qrand() % 256, qrand() % 256, qrand() % 256)));
        blockShapes.append(polygon);
    }
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

void MainWindow::setupLables() {
    timerLabel->setFixedSize(100, 50);
    QFont timerLabelfont("Arial", 20);
    timerLabel->setFont(timerLabelfont);
    timerLabel->setStyleSheet("background-color: black;");
    timerLabel->setAlignment(Qt::AlignCenter);


    levelLabel->setFixedSize(100, 35);
    QFont levelLabelfont("Arial", 15);
    levelLabel->setFont(levelLabelfont);
    levelLabel->setStyleSheet("QLabel { padding: 0px; background-color: grey; border: 1px solid black; }");
    //levelLabel->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_movementModeCheckBox_stateChanged(int state) {
    player->setWrapAroundMovement(state == Qt::Checked);
}

