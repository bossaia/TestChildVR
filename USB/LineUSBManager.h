#ifndef HMDUSBMANAGER_H
#define HMDUSBMANAGER_H
#include <windows.h>
#include <SetupAPI.h>
#include <hidsdi.h>
#include "hidDevice.h"

#define HMDDEVICEMANAGER_API  _declspec(dllexport)
#define  keyvalue VK_RETURN //»Ø³µ
typedef  void(__stdcall  *InputPulseHandler)(int money);
 

extern "C"{
	HMDDEVICEMANAGER_API bool InputPulse(InputPulseHandler iph);
	HMDDEVICEMANAGER_API bool ReceiveMessage(int Massage);
}

 bool InitializeHMDManager();
 bool FreeHMDManager();
 bool CheckHMDConnectState(int VendorID, int ProductID);//OK
 bool ReadDiviceHandle(UCHAR* Report);
 bool OpenHidHandle(UCHAR* DisplayMode);
 bool GetSelectMessage(UCHAR* SelectMessage);
 bool SetSelectMessage(UCHAR SelectMessage);
 bool GetLedMode(UCHAR* LedMode);
 bool SetLedMode(UCHAR* LedMode);
 bool GetLedErrorid(UCHAR* ErrorMode);

#endif