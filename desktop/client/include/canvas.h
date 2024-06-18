#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QFontDatabase>
// include <QFile>
#include <QDebug>

#include <QString>

// here you make the parts for the window module!
// here you use Qpaint
class Canvas : public QWidget
{
private:
    int class_speed = 70;
    int temperature = 0;
    int battery_percentage = 0;
    bool connection = false;
    bool blinker_left = false;
    bool blinker_right = false;
    bool blinker_warning = true;

    QPainter painter;

public:
    Canvas() {}

    void set_speed(int speed);

    void set_temperature(int temp);

    void set_battery_percentage(int charge);

    void set_connection_status(bool status);

    void set_blinker_left(bool mode);

    void set_blinker_right(bool mode);

    void set_blinker_warning(bool mode);

private:
    void paintEvent(QPaintEvent *) override;

    void paint_speed(int speed);

    void paint_battery(int charge);

    void paint_temperature(int temp);

    void paint_light_signal();

    void paint_no_connection();
};

#endif