# Dashboard for EV

This is an embedded programming project with the task of teaching us real time communication via:
1 Local network (TCP/IP)
2 Serial and CAN/BUS communication through ESP32-EVB microcontrollers

The GUI for both client and server are implemented via the QT framework. Serial communication was also implemented via QT.

To manage the different way of communication CMake is used.

Command to use TCP/IP (from root of the project):
mkdir build (if it does not exist)
cd build
cmake ..
make use_tcpip
make
./client && ./server

Commands to use UART and CAN, you need to have the two microcontrollers for this (from root of the project):
mkdir build (if it does not exist)
cd build
cmake ..
make use_uart
make
make upload_client upload_server
./client && ./server

For demostration check out this video:
<https://youtu.be/in1qmFucLsE>
