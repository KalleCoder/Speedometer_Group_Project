#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include "comservice.h"

class TCPService : public COMService
{
public:
    void run() override;

    void processReceivedData();
};

#endif