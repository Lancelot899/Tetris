#ifndef GLWidget_H
#define GLWidget_H

#include <QGLWidget>
#include <QWidget>

#include "Tetris.h"


class GameCanvas : public QGLWidget
{
    Q_OBJECT

public:

public:
    explicit GameCanvas(QWidget* parent=0,
                        const QGLWidget* shareWidget = 0, Qt::WindowFlags f=0);

    ~GameCanvas();

public:
    bool setGame(Tetris *game) {
        if(game == nullptr)
            return false;
        _game = game;
        return true;
    }

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

signals:

public slots:


private:
    Tetris   *_game;
};

class GameCanvasqt : public QWidget
{
    Q_OBJECT

public:
    enum {
        widthMargin = 17,
        heightMargin = 5
    };

public:
    explicit GameCanvasqt(QWidget *parent = 0);

    ~GameCanvasqt() {}

    bool setGame(Tetris *game) {
        if(game == nullptr)
            return false;
        _game = game;
        return true;
    }

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    Tetris   *_game;
};

#endif // GLWidget_H
