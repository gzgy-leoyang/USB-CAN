#ifndef CAN_DEVICE_H
#define CAN_DEVICE_H

#include "can.h"

class can_device
{
public:
    can_device();
    int open_can_port(void);

    int select_device(unsigned int i);

    def_can can_para;
    bool opened;


    int open(void);
    int init(def_can para);
    int startup(void);
    int stop(void);
    int send(void);
    int receive(void);
    unsigned int device_selected ; ///< 标记不同 usb-can 设备，0=阳吉，1=周立功
};

#endif // CAN_DEVICE_H
