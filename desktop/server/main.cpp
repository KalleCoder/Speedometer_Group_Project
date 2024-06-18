#include <QApplication>
#include "window.h"
#include "tcpservice.h"

int main(int argc, char **argv)
{
#ifdef CAN
    QApplication app(argc, argv);

    TCPService service;

    Window window(service);
    window.show();

    return app.exec();
#endif

#ifdef TCIP
    QApplication app(argc, argv);

    TCPService service;

    Window window(service);
    window.show();

    return app.exec();
#endif
}
