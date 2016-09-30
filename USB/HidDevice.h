#ifndef HIDDEVICE_H
#define HIDDEVICE_H

#ifdef _DEBUG
#define FEATURE_DEBUG_SIZE (64)
#endif

#ifndef PAGE_SIZE
#define PAGE_SIZE	(4*1024)
#endif
#include "windows.h"
#include <usbscan.h>
extern "C"{
#include <setupapi.h>
#include <hidsdi.h>
#include <Dbt.h>
}
#include <initguid.h>
#include <pshpack4.h>
#include <poppack.h>


#define USB_DEVINTF_NAME_WIN32_PREFIX	"\\\\?\\USB#VID_XXXX&PID_XXXX"
#define VR_UNKNOWN		            0
#define VR_UNKNOWN_NAME		        "Unknown"
#define VR_OCULUS					1
#define VR_OCULUS_NAME				"Oculus"
#define OCULUS_USD_VID				0x2833


DEFINE_GUID(GUID_DEVINTERFACE_HID, \
	0x4D1E55B2L, 0xF16F, 0x11CF, 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30);
#define GUID_CLASS_INPUT GUID_DEVINTERFACE_HID
#define GUID_CLASS_INPUT_STR "4D1E55B2-F16F-11CF-88CB-001111000030"
#define HIDP_STATUS_SUCCESS (0x11 << 16)


// HID PRE +3
// 00       00      00      CMD 
// CTRL_L   CTRL_H  SIZE_L  SIZE_H              // IAP_CTRL_OFFSET
// DATA...                                      // IAP_DATA_OFFSET
#define IAP_CMD_OFFSET	(FEATURE_HEADER_SIZE)   // 3
#define IAP_CTRL_OFFSET	(IAP_CMD_OFFSET+1)		// 4
#define IAP_SIZE_OFFSET	(IAP_CTRL_OFFSET+2)		// 6
#define IAP_DATA_OFFSET	(IAP_SIZE_OFFSET+2)     // 8
#define IAP_INIT	    0x5A
#define IAP_STATUS		0x00
#define IAP_READ		0x01
#define IAP_WRITE		0x02
#define IAP_DONE		0x10
#define IAP_REBOOT      0x11

#define FW_VER_FIX_DFU   0x0024
#define FW_VER_SWITCH    0x0025
#define MODE_IM2 0xFD
#define MODE_IM1 0xFE
#define HEADER_OFFSET   (0xCC00-0x3000)
#define HEADER_SIGN     0xFFAA5500
// Report ID and Command ID
#define FEATURE_HEADER_SIZE 3
// size in bytes of the packed offset and scale structure
#define CALIBRATION_SIZE (8+8+8*3+8*3+sizeof(unsigned short))

#define FEATURE_CONFIG_SIZE (FEATURE_HEADER_SIZE+4)
#define FEATURE_CALIBRATE_SIZE (FEATURE_HEADER_SIZE+CALIBRATION_SIZE)
#define FEATURE_RANGE_SIZE (FEATURE_HEADER_SIZE+5)
#define FEATURE_REGISTER_SIZE (FEATURE_HEADER_SIZE+3)
#define FEATURE_DFU_SIZE (FEATURE_HEADER_SIZE+1)
#define FEATURE_GPIO_SIZE (FEATURE_HEADER_SIZE+2)
#define FEATURE_KEEP_ALIVE_SIZE (FEATURE_HEADER_SIZE+2)
#define FEATURE_DISPLAY_INFO_SIZE (FEATURE_HEADER_SIZE+53)
#define FEATURE_SERIAL_SIZE (FEATURE_HEADER_SIZE+12)
#define FEATURE_IAP_SIZE (64)
#define FEATURE_MODE_SIZE (FEATURE_HEADER_SIZE+1)
#define FEATURE_LEDMODE_SIZE 17+1
#define FEATURE_ERRORMODE_SIZE (FEATURE_HEADER_SIZE+1)
#define FEATURE_GET_FW_VER_SIZE (FEATURE_HEADER_SIZE+2)
#define FEATURE_GET_MCU_ID_SIZE (FEATURE_HEADER_SIZE+12)



typedef unsigned short UInt16;
struct HIDDeviceDesc
{
	UInt16  VendorId;
	UInt16  ProductId;
	UInt16  VersionNumber;
	UInt16  Usage;
	UInt16  UsagePage;
	//    String  Path;           // Platform specific.
	//    String  Manufacturer;
	//    String  Product;
	//    String  SerialNumber;
	//	WCHAR	Path[MAX_PATH];
	WCHAR	Manufacturer[MAX_PATH];
	WCHAR	Product[MAX_PATH];
	WCHAR	SerialNumber[MAX_PATH];
};
enum {
	FEATURE_CONFIG = 2,
	FEATURE_CALIBRATE = 3,
	FEATURE_RANGE = 4,
	FEATURE_REGISTER = 5,
	FEATURE_DFU_OC = 6,
	FEATURE_DFU = 88,
	FEATURE_MODE = 89,
	FEATURE_BRIGHT = 100,
	FEATURE_GPIO = 7,
	FEATURE_KEEP_ALIVE = 8,
	FEATURE_DISPLAY_INFO = 9,
	FEATURE_SERIAL = 10,

	FEATURE_GET_FW_VER = 95,
	FEATURE_GET_MCU_ID = 96,

	FEATURE_IAP = 97,
	FEATURE_SELECTMESSAGE = 0x80,     //Í¶±Ò
	FEATURE_LEDMODE = 0x81,           //µÆ¹â
	ERROR_ID = 0X82  ,
#ifdef _DEBUG
	FEATURE_DEBUG = 98,
#endif
	FEATURE_MAX = 99
};



HANDLE HIDSIM_CreateHIDFile(const char* path/*, bool exclusiveAccess*/);
bool HIDSIM_GetHMDProductInfo(HANDLE hidDev, HIDDeviceDesc* desc);

BOOLEAN HIDSIM_SetFeatureDfu(HANDLE hidDev, BOOL bEnable);
BOOLEAN HIDSIM_GetFeatureDfu(HANDLE hidDev, UCHAR aBuf[], UINT nlen);

BOOLEAN HIDSIM_GetFeatureMode(HANDLE hidDev, UCHAR aBuf[], UINT nlen);
BOOLEAN HIDSIM_SetFeatureMode(HANDLE hidDev, UCHAR uMode);

BOOLEAN HIDSIM_GetFeatureIAP(HANDLE hidDev, UCHAR aBuf[], UINT nlen);
BOOLEAN HIDSIM_SetFeatureIAP(HANDLE hidDev, UCHAR aBuf[], UINT nlen);

BOOLEAN HIDSIM_GetFeatureFwVer(HANDLE hidDev, UCHAR aBuf[], UINT nlen);
BOOLEAN HIDSIM_GetFeatureMcuId(HANDLE hidDev, UCHAR aBuf[], UINT nlen);

#ifdef _DEBUG
BOOLEAN HIDSIM_GetFeatureDebug(HANDLE hidDev, UCHAR aBuf[], UINT nlen);
BOOLEAN HIDSIM_SetFeatureDebug(HANDLE hidDev, UCHAR aBuf[], UINT nlen);
#endif

bool HIDSIM_initUsage(HANDLE hidDev, HIDDeviceDesc* desc);
void HIDSIM_initStrings(HANDLE hidDev, HIDDeviceDesc* desc);
bool HIDSIM_getFullDesc(HANDLE hidDev, HIDDeviceDesc* desc); //const

CHAR * HIDSIM_GetHidDeviceWin32Path(CHAR *pHidGuid, WORD Vid, WORD Pid);
VOID HIDSIM_OnDbtDeviceArrival(/*HWND hWnd, */DEV_BROADCAST_HDR *pDevHdr);
BOOLEAN HIDSIM_GetFeatureBright(HANDLE hidDev, UCHAR aBuf[], UINT nlen);
BOOLEAN HIDSIM_SetFeatureBright(HANDLE hidDev, UCHAR NUM);
#endif