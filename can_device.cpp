#include "can_device.h"

#include "VCI_DLL.h"


can_device::can_device()
{
    device_selected = 0;
    can_para.buadrate = 250000;
    can_para.port_num = 0;   // can0
    can_para.frame_type = 0; // extend frame
    can_para.mode = 0;       // normal
    opened = false;
}

int can_device::select_device(unsigned int i)
{
    device_selected = i;
    return 0;
}

int can_device::open_can_port(void)
{
    if ( open() < 0 ){
        return -1;
    }

    if ( init(can_para) < 0 ){
        return -1;
    }

    if ( startup() < 0 ){
        return -1;
    }
    opened = true;
    return 0;
}

// 更换 USB-CAN adpator,修改以下部分
int can_device::open(void)
{
    if ( device_selected == 0 ){
        if (VCI_OpenDevice(DEV_USBCAN,1,0)){
            return 0;
        } else {
            return -1;
        }
    } else {

    }
    return -1;
}

int can_device::init(def_can para)
{
    VCI_INIT_CONFIG InitInfo[1];

    can_para = para;

    if ( device_selected == 0 ){
        InitInfo->kCanBaud=10;//250k
        InitInfo->Timing0=0x01;
        InitInfo->Timing1=0x1C;
        InitInfo->Filter=0;
        InitInfo->AccCode=0x80000008;
        InitInfo->AccMask=0xFFFFFFFF;
        InitInfo->Mode=0;
        InitInfo->CanRx_IER=1;

        if( VCI_InitCAN(DEV_USBCAN,1, 0,InitInfo)){
            return 0;
        }else {
            return -1;
        }
    } else {

    }

    return -1;
}

int can_device::startup(void)
{
    if ( device_selected == 0 ){
        if ( VCI_StartCAN(DEV_USBCAN,1,0) ){
            return 0;
        } else {
            return -1;
        }
    } else {

    }

    return -1;
}

int can_device::stop(void)
{
    if ( device_selected == 0 ){
        VCI_CloseDevice(DEV_USBCAN,0);
    } else {

    }

    return 0;
}

int can_device::send(void)
{
    VCI_CAN_OBJ sendbuf[1];
    unsigned char SendID[10];
    unsigned char SendID2[4];
    unsigned char buf[50];
    unsigned int i = 0;

    sendbuf->ExternFlag=0;
    sendbuf->DataLen=8;
    sendbuf->RemoteFlag=0;

    SendID[0] &= 0x1F;
    SendID2[0]=(SendID[0]<<3)|(SendID[1]>>5);
    SendID2[1]=(SendID[1]<<3)|(SendID[2]>>5);
    SendID2[2]=(SendID[2]<<3)|(SendID[3]>>5);
    SendID2[3]=(SendID[3]<<3);

    for(i=0;i<4;i++)
        sendbuf->ID[i]=SendID2[i];

    for(i=0;i<8;i++)
        sendbuf->Data[i]=buf[i];

    VCI_Transmit(DEV_USBCAN,0,0,sendbuf);
    return 0;
}

int can_device::receive(void)
{
    VCI_CAN_OBJ pCanObj[200];
    int Len = 0;

    Len = VCI_Receive(DEV_USBCAN,0,0,pCanObj);
    return Len;
}
