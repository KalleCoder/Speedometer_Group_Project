#ifndef TCPCOM_H
#define TCPCOM_H

#include "comservice.h"

class TCPService : public COMService
{
public:
    void run() override;
};

#endif