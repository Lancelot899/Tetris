#include <QDebug>
#include <QPainter>
#include <QPixmap>

#include "GameCanvas.h"



GameCanvas::GameCanvas(QWidget *parent, const QGLWidget *shareWidget, Qt::WindowFlags f) :
    QGLWidget(parent, shareWidget, f) {}

GameCanvas::~GameCanvas() {}

void GameCanvas::initializeGL() {
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0, 1.0, 1.0, 0);

    glEnable(GL_DEPTH_BITS);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //this->format().setDoubleBuffer(true);
}

void GameCanvas::paintGL() {
    //this->swapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef( 180.0f, 0.0, 0.0, 1.0 );
    glTranslatef(0, 0, -0.1);

/*
    glBegin( GL_TRIANGLES );
    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f( 0.0, 0.01, 0.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( -1.0, -1.0, 0.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( 1.0, -1.0, 0.0 );
    glEnd();
*/
    //qDebug() << "repaint";

    // draw map
    if(_game->getMap().get()) {
        //qDebug() << "paint map";
        float bw = 2.0f / float(_game->getMap()->getMapWidth());
        float bh = 2.0f / float(_game->getMap()->getMapHeight());
        //qDebug() << bw;
        //qDebug() << bh;
        for(int i = -_game->getMap()->getMapWidth(); i < _game->getMap()->getMapWidth(); ++i) {
            glBegin(GL_LINES);
            glColor3f(0,0,0);
            glVertex3f(i * bw , -1.0f, 0);
            glColor3f(0,0,0);
            glVertex3f(i * bw, 1.0f, 0.0);
            glEnd();
        }
        for(int j = -_game->getMap()->getMapHeight(); j < _game->getMap()->getMapHeight(); ++j) {
            glBegin(GL_LINES);
            glColor3f(0,0,0);
            glVertex3f(-1.0, j * bh, 0);
            glColor3f(0,0,0);
            glVertex3f(1.0, j * bh, 0.0);
            glEnd();
        }

        float r = 0.0f, g = 0.0f, b = 0.0f; int pos[8] = {0};
        if(_game->getCurBlock().get() != nullptr) {
            // set current block color
            switch (_game->getCurBlock()->getShape()) {
            case BlockType::Shape_O :
                b = 1.0f;
                break;
            case BlockType::Shape_I :
                r = 1.0f; b = 1.0f;
                break;
            case BlockType::Shape_J :
                r = 1.0f;
                break;
            case BlockType::Shape_L :
                r = 1.0f; g = 38.0f / 255.0f; b = 125.0f / 255.0f;
                break;
            case BlockType::Shape_S :
                r = 25.0f / 255.0f;
                g = 30.0f / 255.0f;
                b = 1.0f;
                break;
            case BlockType::Shape_T :
                g = 1.0f;
                break;
            case BlockType::Shape_Z :
                b = 1.0f; g = 1.0f;
                break;
            default:
                break;
            }
            // get current block pos
            _game->getCurBlock()->getBlock(pos);
        }

        //_game->getMap()->at(0, 0) = 1;
        // draw
        for(int i = -_game->getMap()->getMapWidth(); i + 1 < _game->getMap()->getMapWidth(); ++i) {
            for(int j = -_game->getMap()->getMapHeight(); j + 1 < _game->getMap()->getMapHeight(); ++j) {
                //qDebug() << i << j;
                //qDebug() << idx << idy;
                if((i + _game->getMap()->getMapHeight() == pos[0] ||
                    i + _game->getMap()->getMapHeight() == pos[2] ||
                    i + _game->getMap()->getMapHeight() == pos[4] ||
                    i + _game->getMap()->getMapHeight() == pos[6])
                        && (j + _game->getMap()->getMapHeight() == pos[1] ||
                            j + _game->getMap()->getMapHeight() == pos[3] ||
                            j + _game->getMap()->getMapHeight() == pos[5] ||
                            j + _game->getMap()->getMapHeight() == pos[7])) {
                        glBegin(GL_QUADS);
                        glColor3f( r, g, b );
                        glVertex3f(i * bw, j * bh, 0);
                        glColor3f( r, g, b );
                        glVertex3f(i * bw, (j + 1) * bh, 0);
                        glColor3f( r, g, b );
                        glVertex3f((i + 1) * bw, (j + 1) * bh, 0);
                        glColor3f( r, g, b );
                        glVertex3f((i + 1) * bw, j * bh, 0);
                        glEnd();
                        //qDebug() << "i = " << i<<"\t j = "<< j;
                        //qDebug() << "i * bw = "<<  i * bw << "\t j * bh = "<< j * bh;
                }

                if(_game->getMap()->at(i + _game->getMap()->getMapWidth(), j + _game->getMap()->getMapHeight())) {
                    qDebug() << "i = " << i + _game->getMap()->getMapWidth() <<"\t j = "<< j + _game->getMap()->getMapHeight();
                    qDebug() << "i * bw = "<<  i * bw << "\t j * bh = "<< j * bh;
                    glBegin(GL_QUADS);
                    glColor3f( 159.0 / 255.0, 254 / 255.0, 255.0 / 255.0 );
                    glVertex3f(i * bw, j * bh, 0);
                    glColor3f( 159.0 / 255.0, 254 / 255.0, 255.0 / 255.0 );
                    glVertex3f(i * bw, (j + 1) * bh, 0);
                    glColor3f( 159.0 / 255.0, 254 / 255.0, 255.0 / 255.0 );
                    glVertex3f((i + 1) * bw, (j + 1) * bh, 0);
                    glColor3f( 159.0 / 255.0, 254 / 255.0, 255.0 / 255.0 );
                    glVertex3f((i + 1) * bw, j * bh, 0);
                    glEnd();

                }
            }
        }
    }

}

void GameCanvas::resizeGL(int width, int height) {
    if(!height)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



GameCanvasqt::GameCanvasqt(QWidget *parent)
    : QWidget(parent){

}

void GameCanvasqt::paintEvent(QPaintEvent *){
    if(_game->getMap().get()) {
        QSize winSize = this->size();
        //qDebug() << winSize;
        QPixmap map(winSize.width() - widthMargin, winSize.height() - heightMargin);
        QSize mapSize = map.size();
        map.fill();
        QPainter p(&map);
        p.setPen(Qt::black);

        // draw map
        int bw = mapSize.width() / Tetris::MapWidth;
        int bh = mapSize.height() / Tetris::MapHeight;
        for(int i = 0; i < Tetris::MapWidth; ++i) {
            for(int j = 0; j < Tetris::MapHeight; ++j) {
                //p.setPen(QColor(0, 0, 0));
                if(_game->getMap()->at(i, j)) {
                    p.setBrush(QBrush(QColor(159, 254, 255)));
                    p.drawRect(i * bw, j * bh, bw, bh);
                }
                else {
                    p.setBrush(QBrush(QColor(255, 255, 255)));
                    p.drawRect(i * bw, j * bh, bw, bh);
                }
            }
        }

        if(_game->isRunning()) {
            // draw block
            int r = 0, g = 0, b = 0;
            int pos[8];
            memset(pos, 0, sizeof(int) * 8);
            switch (_game->getCurBlock()->getShape()) {
            case BlockType::Shape_O :
                b = 255;
                break;
            case BlockType::Shape_I :
                r = 255; b = 255;
                break;
            case BlockType::Shape_J :
                r = 255;
                break;
            case BlockType::Shape_L :
                r = 255; g = 38; b = 125;
                break;
            case BlockType::Shape_S :
                r = 25;
                g = 30;
                b = 255;
                break;
            case BlockType::Shape_T :
                g = 255;
                break;
            case BlockType::Shape_Z :
                b = 255; g = 255;
                break;
            default:
                break;
            }
            _game->getCurBlock()->getBlock(pos);

            for(int i = 0; i <= 3; ++i) {
                p.setBrush(QBrush(QColor(r, g, b)));
                p.drawRect(pos[2 * i] * bw, pos[i * 2 + 1] * bh, bw, bh);
            }
        }


        p.end();
        p.begin(this);
        p.drawPixmap(widthMargin / 2, heightMargin / 2, map);
        p.end();
    }


}
