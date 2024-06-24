#include <QApplication>
#include "window.h"
#include "tcpservice.h"

int main(int argc, char **argv)
{
#ifdef TCP
    QApplication app(argc, argv);

    TCPService service;

    Window window(service);
    window.update();
    window.show();

    return app.exec();
#endif
#ifndef TCP
    QApplication app(argc, argv);

    TCPService service;

    Window window(service);
    window.update();
    window.show();

    // service.run(); // THIS NEEDS A THREAD!

    return app.exec();
#endif
}
