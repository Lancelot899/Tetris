#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>

#include <QLineEdit>
#include <QTimer>

#include "Tetris.h"


class GameCanvas;
class GameCanvasqt;
class NextBlockCanvas;

class MainWidget : public QWidget {
    Q_OBJECT

public:
    enum {
        WinWidth = 480,
        WinHeight = 500
    };


public:
    explicit MainWidget(QWidget *parent = 0);

signals:

public slots:
    void gmStart();
    void tmStart();
    void gmPause();
    void gmReset();

protected:
    void keyPressEvent(QKeyEvent *ev);
    bool event(QEvent *ev);


private:
    void Update();

private:
    bool                _isFullScreen;
    GameCanvasqt        *_gameWidget;
    QPushButton         *_stButton;
    QPushButton         *_pauseButton;
    QPushButton         *_resetButton;
    NextBlockCanvas     *_nextBlock;
    QLineEdit           *_gameTimes;
    QLineEdit           *_gamePoint;
    QLineEdit           *_gameMaxPoint;
    QTimer              _startTimer;
    int                 _timestamp;
//    QTimer              _runningTimer;

private:
    Tetris              _game;
};

#endif // MAINWIDGET_H
