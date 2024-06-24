#ifndef WINDOW_H
#define WINDOW_H

#include "canvas.h"
#include "comservice.h"
#include <QDialog>
#include <QVBoxLayout>

// here you have an instance of canvas
// making the layout
// you get information from the communication to the window,
// and use the canvas module to draw the information
class Window : public QDialog
{
    COMService &comservice;

private:
    Canvas canvas;
    QVBoxLayout layout;

public:
    Window(COMService &comsrv);
    // Window();

    void update();
    // void update(COMService &comservice);
};

#endif