#include "window.h"

// Window(COMService &comservise)
Window::Window()
{
    setWindowTitle("client");
    setFixedSize(800, 560);

    // Set background color of the window
    setStyleSheet("background-color: rgb(60, 0, 70);");

    // Adjust layout margins
    layout.setContentsMargins(0, 0, 0, 0); // Set margins to zero

    layout.addWidget(&canvas); // Add the canvas directly to the layout
    setLayout(&layout);
}

/// HERE YOU SHOULD USE THE COMSERVICE FUNCTIONS TO GET THE VALUES!
void Window::update()
{
    canvas.set_connection_status(true);
    canvas.set_speed(0);
    canvas.set_battery_percentage(0);
    canvas.set_temperature(0);
    canvas.set_blinker_left(false);
    canvas.set_blinker_right(false);
    canvas.set_blinker_warning(false);
}