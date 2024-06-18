#include "include/window.h"
#include <QApplication>

int main(int argc, char **argv)
{
#ifdef CAN
    QApplication app(argc, argv);

    Window window;
    window.show();

    return app.exec();
#endif

#ifdef TCIP
    QApplication app(argc, argv);

    Window window;
    window.show();

    return app.exec();
#endif
}
