#include <time.h>
#include <stdlib.h>

#include <QApplication>

#include "MainWidget.h"


int main(int argc, char *argv[]) {
    time_t tm;
    time(&tm);
    srand(tm);

    QApplication app(argc, argv);
    MainWidget w;
    w.show();

    return app.exec();
}

