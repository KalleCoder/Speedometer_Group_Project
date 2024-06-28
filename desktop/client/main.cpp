#include "window.h"
#include "tcpservice.h"
#include <thread>
#include <QApplication>
#include <QTimer>

void setup(Window &window)
{
    constexpr int interval = 20; // 20 milliseconds

    QTimer *timer = new QTimer(&window); // Timer will be deleted with window
    QObject::connect(timer, &QTimer::timeout, [&window]()
                     { window.update(); });

    timer->start(interval);
}

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
    std::thread tcpThread(&TCPService::run, &service);
    tcpThread.detach();

    setup(window);
    // window.update();

    window.show();

    return app.exec();
#endif
}
