#include <stdlib.h>
#include <iostream>

#include <QMessageBox>
#include <QKeyEvent>
#include <QEvent>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

#include "MainWidget.h"
#include "GameCanvas.h"


class NextBlockCanvas : public QWidget {

public:
    NextBlockCanvas(QWidget *parent = 0);
    ~NextBlockCanvas() {}

    void paintEvent(QPaintEvent *);
    void setBlock(BlockType blockType) {
        _nextBlockType = blockType;
    }

private:
    BlockType             _nextBlockType;
};


NextBlockCanvas::NextBlockCanvas(QWidget *parent)
    : QWidget(parent), _nextBlockType(Shape_None){

}

void NextBlockCanvas::paintEvent(QPaintEvent *) {
    int w, h;
    int bw, bh;

    w = this->width();
    h = this->height();
    bw = w / 4;
    bh = h / 4;


    QPainter painter(this);

    // clear background
    painter.setBrush(QBrush(QColor(255, 255, 255)));
    painter.setPen(QColor(0, 0, 0));
    painter.drawRect(QRect(0, 0, w-1, h-1));


    int b[8];
    bool isPtBck = true;
    memset(b, 0, sizeof(int) * 8);

    switch(_nextBlockType) {
    case Shape_O:
        painter.setBrush(QBrush(QColor(0, 0, 255)));
        painter.setPen(QColor(0, 0, 0));
        b[0] = 1;
        b[1] = 1;
        b[2] = 2;
        b[3] = 1;
        b[4] = 1;
        b[5] = 2;
        b[6] = 2;
        b[7] = 2;
        break;
    case Shape_T:
        painter.setBrush(QBrush(QColor(0, 255, 0)));
        painter.setPen(QColor(0, 0, 0));
        b[0] = 1;
        b[1] = 1;
        b[2] = 0;
        b[3] = 2;
        b[4] = 1;
        b[5] = 2;
        b[6] = 2;
        b[7] = 2;
        break;
    case Shape_J:
        painter.setBrush(QBrush(QColor(255, 0, 0)));
        painter.setPen(QColor(0, 0, 0));
        b[0] = 0;
        b[1] = 1;
        b[2] = 1;
        b[3] = 1;
        b[4] = 2;
        b[5] = 1;
        b[6] = 2;
        b[7] = 2;
        break;
    case Shape_Z:
        painter.setBrush(QBrush(QColor(0, 255, 255)));
        painter.setPen(QColor(0, 0, 0));
        b[0] = 0;
        b[1] = 1;
        b[2] = 1;
        b[3] = 1;
        b[4] = 1;
        b[5] = 2;
        b[6] = 2;
        b[7] = 2;
        break;
    case Shape_I:
        painter.setBrush(QBrush(QColor(255, 0, 255)));
        painter.setPen(QColor(0, 0, 0));
        b[0] = 0;
        b[1] = 1;
        b[2] = 1;
        b[3] = 1;
        b[4] = 2;
        b[5] = 1;
        b[6] = 3;
        b[7] = 1;
        break;
    case Shape_S:
        painter.setBrush(QBrush(QColor(25, 30, 255)));
        painter.setPen(QColor(0, 0, 0));
        b[0] = 1;
        b[1] = 1;
        b[2] = 2;
        b[3] = 1;
        b[4] = 0;
        b[5] = 2;
        b[6] = 1;
        b[7] = 2;
        break;
    case Shape_L:
        painter.setBrush(QBrush(QColor(255, 38, 125)));
        painter.setPen(QColor(0, 0, 0));
        b[0] = 1;
        b[1] = 1;
        b[2] = 2;
        b[3] = 1;
        b[4] = 3;
        b[5] = 1;
        b[6] = 1;
        b[7] = 2;
        break;
    default:
        isPtBck = false;
        break;
    }



    // draw blocks
    if(isPtBck) {
        int x, y, ix, iy;
        for(int i=0; i<4; i++) {
            ix = b[i*2+0];
            iy = b[i*2+1];
            x = ix*bw;
            y = iy*bh;
            painter.drawRect(QRect(x, y, bw, bh));
    }

    painter.end();
    }
}



MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent), _isFullScreen(false) , _timestamp(0) {
    if(QMessageBox::Yes == QMessageBox::information(0, "Start FullScreen?"
                                                   , "Would You Like To Run In Fullscreen Mode?",
                                                   QMessageBox::Yes, QMessageBox::No | QMessageBox::Default)) {
        _isFullScreen = true;
    }

    QGridLayout *mainLayout = new QGridLayout(this);
    QLabel              *_gameTimesLabel;
    QLabel              *_gamePointLabel;
    QLabel              *_gameMaxPointLabel;
    QGroupBox           *_gameMsg;

    mainLayout->addWidget(_gameWidget = new GameCanvasqt(this), 0, 0, 5, 8);
    mainLayout->addWidget(_stButton = new QPushButton("start"), 6, 0);
    mainLayout->addWidget(_pauseButton = new QPushButton("pause"), 6, 2);
    mainLayout->addWidget(_resetButton = new QPushButton("reset"), 6, 4);
    mainLayout->addWidget(_nextBlock = new NextBlockCanvas(this), 0, 9, 2, 2);
    mainLayout->addWidget(_gameMsg = new QGroupBox, 2,9, 2, 2);

    _gameMsg->setTitle("game message");

    QHBoxLayout *gmsgLay = new QHBoxLayout;
    QVBoxLayout *gmsglLay = new QVBoxLayout;
    QVBoxLayout *gmsgrLay = new QVBoxLayout;

    gmsgLay->addLayout(gmsglLay);
    gmsgLay->addLayout(gmsgrLay);

    gmsglLay->addWidget(_gameTimesLabel = new QLabel);
    gmsglLay->addWidget(_gameMaxPointLabel = new QLabel);
    gmsglLay->addWidget(_gamePointLabel = new QLabel);

    gmsgrLay->addWidget(_gameTimes = new QLineEdit);
    gmsgrLay->addWidget(_gameMaxPoint = new QLineEdit);
    gmsgrLay->addWidget(_gamePoint = new QLineEdit);

    _gameTimesLabel->setText("play times");
    _gameMaxPointLabel->setText("the max point");
    _gamePointLabel->setText("current point");

    _gamePoint->setReadOnly(true);
    _gameTimes->setReadOnly(true);
    _gameMaxPoint->setReadOnly(true);

    _gameMsg->setLayout(gmsgLay);
    this->setLayout(mainLayout);
    setWindowTitle("Tetris");

    if(_isFullScreen)
        showFullScreen();
    else{
        showNormal();
        setFixedSize(WinWidth, WinHeight);
    }
    _gameMaxPoint->setText("0");
    _gamePoint->setText("0");
    _gameTimes->setText("0");
    _gameWidget->setGame(&_game);

    connect(_stButton, SIGNAL(clicked()), this, SLOT(gmStart()));
    connect(&_startTimer, SIGNAL(timeout()), this, SLOT(tmStart()));
    //connect(&_runningTimer, SIGNAL(timeout()), this, SLOT(tmRunning()));
    connect(_pauseButton, SIGNAL(clicked()), this, SLOT(gmPause()));
    connect(_resetButton, SIGNAL(clicked()), this, SLOT(gmReset()));
}

void MainWidget::gmStart() {
    //Update();
    _startTimer.start(30);
}

void MainWidget::tmStart() {
    if(_game.isRunning() == false) {
        _game.run();
        _nextBlock->setBlock(_game.getNextBlockType());
        Update();
    }

    if(_timestamp == 50) {
        // running
        _nextBlock->setBlock(_game.getNextBlockType());
        _game.action(Tetris::Down);
        Update();
        if(_game.isOver()) {
            QMessageBox::information(this, "game over!", "game over!!!", QMessageBox::Ok);
            gmPause();
            _gameMaxPoint->setText(QString(QChar('0' + _game.getMaxPoint())));
            _gameTimes->setText(QString(QChar('0' + _game.getPlayTimes())));
        }
        else
            _gamePoint->setText(QString(QChar('0' + _game.getCurPoint())));

        _timestamp = 0;
    }
    else
        ++_timestamp;
}


void MainWidget::gmPause() {
    _game.pause();
    _timestamp = 0;
    _startTimer.stop();
}

void MainWidget::gmReset() {
    gmPause();
    if(QMessageBox::Yes ==
            QMessageBox::question(this,
                          "really restart?",
                          "do you want to restart really?",
                          QMessageBox::No,
                          QMessageBox::Yes | QMessageBox::Default)) {
        _game.reset();
    }
    gmStart();
}

void MainWidget::keyPressEvent(QKeyEvent *ev) {
    switch(ev->key()) {
    case Qt::Key_Escape:
        if(QMessageBox::Yes ==
                QMessageBox::question(this,
                              "really exit?",
                              "do you want to exit really?",
                              QMessageBox::No,
                              QMessageBox::Yes | QMessageBox::Default))
        close();
    case Qt::Key_W:
        _game.action(Tetris::Rotate);
        //qDebug() << "rotate:" << res;
        break;

    case Qt::Key_A:
        _game.action(Tetris::Left);
        break;

    case Qt::Key_D :
        _game.action(Tetris::Right);
        break;

    case Qt::Key_S:
        _game.action(Tetris::Down);
        break;

    default:
        break;
    }
    update();
    //qDebug() << res;
}

bool MainWidget::event(QEvent *ev) {
    return QWidget::event(ev);
}

void MainWidget::Update() {
    char buf[32];
    memset(buf, 0, sizeof(char) * 32);
    sprintf(buf, "%d", _game.getCurPoint());
    //std::cout << buf << std::endl;
    _gamePoint->setText(QString(buf));

    update();
//    _gameWidget->updateGL();
}


