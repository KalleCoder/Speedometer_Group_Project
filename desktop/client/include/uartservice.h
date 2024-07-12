#ifndef UARTSERVICE_H
#define UARTSERVICE_H

#include "comservice.h"

class UARTService : public COMService
{
public:
    void run() override;
};

#endif