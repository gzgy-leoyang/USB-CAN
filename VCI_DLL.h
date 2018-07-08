//#include "ControlCAN.h"

#define REFTYPE_MODE		0
#define REFTYPE_FILTER		1
#define REFTYPE_ACR0		2
#define REFTYPE_ACR1		3
#define REFTYPE_ACR2		4
#define REFTYPE_ACR3		5
#define REFTYPE_AMR0		6	
#define REFTYPE_AMR1		7	
#define REFTYPE_AMR2		8	
#define REFTYPE_AMR3		9
#define REFTYPE_kCANBAUD	10	
#define REFTYPE_TIMING0		11
#define REFTYPE_TIMING1		12
#define REFTYPE_CANRX_EN	13
#define REFTYPE_UARTBAUD	14
#define REFTYPE_ALL			15

#define REFTYPE_DEVICE_IP0	16
#define REFTYPE_DEVICE_IP1	17
#define REFTYPE_DEVICE_IP2	18
#define REFTYPE_DEVICE_IP3	19
#define REFTYPE_HOST_IP0	20
#define REFTYPE_HOST_IP1	21
#define REFTYPE_HOST_IP2	22
#define REFTYPE_HOST_IP3	23

#define REFTYPE_BORRD_INFO	32


//�ӿڿ����Ͷ���

#define DEV_CAN232B		1
#define DEV_USBCAN		2
#define DEV_USBCAN200		3
#define DEV_NETCAN		4
#define DEV_NETCAN200		5
#define DEV_PCICAN200		6



//�������÷���״ֵ̬
#define	STATUS_OK					1
#define STATUS_ERR1					0//����ʧ��
#define STATUS_ERR2					-1 //�豸δ��
	

//1.GY85XXϵ��CAN�ӿڿ���Ϣ���������͡�
typedef  struct  _VCI_BOARD_INFO{
		unsigned short	hw_Version;
		unsigned short	fw_Version;
		unsigned short	dr_Version;
		unsigned short	in_Version;
		unsigned short	irq_Num;
	    unsigned char	can_Num;
		char	str_Serial_Num[8];
		char	str_hw_Type[16];
		char	str_GYUsb_Serial[4][4];
	
} VCI_BOARD_INFO,*PVCI_BOARD_INFO; //��63���ֽ�

//2.����CAN��Ϣ֡���������͡�
typedef  struct  _VCI_CAN_OBJ{
	unsigned char	ID[4];
	unsigned int	TimeStamp;
	unsigned char	TimeFlag;
	unsigned char	SendType;//������ yyd
	unsigned char	RemoteFlag;//�Ƿ���Զ��֡
	unsigned char	ExternFlag;//�Ƿ�����չ֡
	unsigned char	DataLen;
	unsigned char	Data[8];
	unsigned char	Reserved[3];
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;

//3.����CAN������״̬���������͡�
typedef struct _VCI_CAN_STATUS{
	unsigned char	ErrInterrupt;
	unsigned char	regMode;
	unsigned char	regStatus;
	unsigned char	regALCapture;
	unsigned char	regECCapture; 
	unsigned char	regEWLimit;
	unsigned char	regRECounter; 
	unsigned char	regTECounter;
	unsigned long	Reserved;
}VCI_CAN_STATUS,*PVCI_CAN_STATUS;

//4.���������Ϣ���������͡�
typedef struct _ERR_INFO{
		unsigned int	ErrCode;
		unsigned char	Passive_ErrData[3];
		unsigned char	ArLost_ErrData;
} VCI_ERR_INFO,*PVCI_ERR_INFO;

//5.�����ʼ��CAN����������
typedef struct _INIT_CONFIG{
	unsigned long	AccCode;
	unsigned long	AccMask;
	unsigned long	Reserved;
	unsigned char	Filter;
	unsigned char	kCanBaud;
	unsigned char	Timing0;	
	unsigned char	Timing1;	
	unsigned char	Mode;
	unsigned char	CanRx_IER;//added by yyd
}VCI_INIT_CONFIG,*PVCI_INIT_CONFIG;

extern "C"
{

	unsigned long __stdcall VCI_OpenDevice(unsigned long DeviceType,unsigned long DeviceInd,unsigned long Reserved);
	unsigned long __stdcall VCI_CloseDevice(unsigned long DeviceType,unsigned long DeviceInd);
	unsigned long __stdcall VCI_InitCAN(unsigned long DeviceType, unsigned long DeviceInd, unsigned long CANInd, PVCI_INIT_CONFIG pInitConfig);

	unsigned long __stdcall VCI_ResumeConfig(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd);

	unsigned long __stdcall VCI_WriteBoardInfo(unsigned long DeviceType,unsigned long DeviceInd,PVCI_BOARD_INFO pInfo);
	unsigned long __stdcall VCI_ReadBoardInfo(unsigned long DeviceType,unsigned long DeviceInd,PVCI_BOARD_INFO pInfo);

	unsigned long __stdcall VCI_ReadErrInfo(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,PVCI_ERR_INFO pErrInfo);
	unsigned long __stdcall VCI_ReadCANStatus(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,PVCI_CAN_STATUS pCANStatus);

	unsigned long __stdcall VCI_GetReference(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,unsigned long RefType,unsigned char *pData);
	unsigned long __stdcall VCI_SetReference(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,unsigned long RefType,unsigned char *pData);

	unsigned long __stdcall VCI_GetReceiveNum(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd);
	unsigned long __stdcall VCI_ClearBuffer(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd);

	unsigned long __stdcall VCI_StartCAN(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd);
	unsigned long __stdcall VCI_ResetCAN(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd);

	unsigned long __stdcall VCI_Transmit(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,PVCI_CAN_OBJ pSend);
	unsigned long __stdcall VCI_Receive(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,PVCI_CAN_OBJ pReceive);

	unsigned long __stdcall VCI_FindGyUsbDevice(PVCI_BOARD_INFO pInfo);
	unsigned long __stdcall VCI_UsbDeviceReset(unsigned long DeviceType,unsigned long DeviceInd,unsigned long Reserved);
}