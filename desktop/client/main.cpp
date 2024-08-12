#include "window.h"
#include "tcpservice.h"
#include <thread>
#include <QApplication>
#include <QTimer>
#include <chrono>
#include <atomic>

void setup(Window &window)
{
    constexpr int interval = 20; // 20 milliseconds

    QTimer *timer = new QTimer(&window); // Timer will be deleted with window
    QObject::connect(timer, &QTimer::timeout, [&window]()
                     {
                         qDebug() << "Updating window";
                         window.update(); });

    timer->start(interval);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    TCPService service;
    Window window(service);
    std::thread tcpThread(&TCPService::run, &service);
    tcpThread.detach();

    // setup(window);

    // Using a separate thread for periodic updates
    std::thread updateThread([&window]()
                             {
        while (true)
        {
            //std::this_thread::sleep_for(std::chrono::milliseconds(20)); // why this sleep?
            window.update();  // Call the update method
        } });

    // window.update();

    window.show();

    return app.exec();
}
