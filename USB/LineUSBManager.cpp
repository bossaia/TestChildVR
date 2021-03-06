
#include "LineUSBManager.h"
#include "HidDevice.h"
#include "stdio.h"
//#include "afxwin.h"
//Application global variables 
#define  keyvalue VK_RETURN

int VendorID = 0x036d;  //VendorID = 0x036d;
int ProductID = 0xc21f;   //ProductID = 0xc21f;
UCHAR SelectMessage[2] = { 0 };  //SelectMessage[0]表示投币帧编号，SelectMessage[1]表示错误代码
UCHAR receive_error[2] = { 0 };
UCHAR receive_time = 0;
bool AAS = FALSE;  //给顶层重复发数据标志位；
UCHAR coin = 0;    //投币数据
//        帧头 序号  时间   灯1  灯2    灯3   灯4   灯5   灯6  灯7   灯8   灯9   灯10  灯11  灯12  灯13  灯14 /
/*UCHAR Led_buffer[100][17] = { { 0x81, 0x00, 0x64, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x81, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
{ 0x81, 0x02, 0x05, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x03, 0x05, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00 },
{ 0x81, 0x04, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x05, 0x05, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00 },
{ 0x81, 0x06, 0x05, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x07, 0x05, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00 },
{ 0x81, 0x08, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x09, 0x04, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00 },
{ 0x81, 0x0a, 0x0e, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x0b, 0x04, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x0c, 0x0e, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x0d, 0x04, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x0e, 0x0e, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x0f, 0x04, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x10, 0x0e, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x11, 0x06, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x12, 0x0c, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x13, 0x06, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x14, 0x0c, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x15, 0x06, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x16, 0x0c, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x17, 0x06, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x18, 0x0c, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x19, 0x08, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x1a, 0x0a, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x1b, 0x08, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x1c, 0x0a, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x1d, 0x08, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x1e, 0x0a, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x1f, 0x08, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x20, 0x0a, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x21, 0x0a, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x22, 0x08, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x23, 0x0a, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x24, 0x08, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x25, 0x0a, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x26, 0x08, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x27, 0x0a, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x28, 0x08, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x29, 0x0c, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x2a, 0x06, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x2b, 0x0c, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x2c, 0x06, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x2d, 0x0c, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x2e, 0x06, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x2f, 0x0c, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x30, 0x06, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x31, 0x0e, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x32, 0x04, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x33, 0x0e, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x34, 0x04, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x35, 0x0e, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x36, 0x04, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x37, 0x0e, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x38, 0x04, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x39, 0x10, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x3a, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x3b, 0x10, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x3c, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x3d, 0x10, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01 },
{ 0x81, 0x3e, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x3f, 0x10, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
{ 0x81, 0x38, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 },
};
*/
UCHAR Get_Led_buffer[17] = { 0 };
UCHAR n = 0;
UINT TimerId;
UCHAR TimerOn = 0;
bool ClearFlag = TRUE;
GUID								MyHidGuid;
HANDLE								hDevInfo;
bool								MyDeviceDetected = FALSE;
bool connect_flag = FALSE;
CHAR*						        MyDevicePathName;
HANDLE								DeviceHandle;
HANDLE                              ReadHandle;
DWORD								ActualBytesRead;
DWORD								BytesRead;
DWORD								cbBytesRead;
PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
HANDLE                              m_hWnd;

DWORD								NumberOfBytesRead;
char								OutputReport[256];
ULONG								Required;
char*							    ValueToDisplay;


DWORD								dwError;
char								FeatureReport[256];
HANDLE								hEventObject;

OVERLAPPED							HIDOverlapped;
char								InputReport[256];
ULONG								Length;
LPOVERLAPPED						lpOverLap;


// Compute Device Class: this is used to get the tree contrl root icon
static const GUID GUID_DEVCLASS_COMPUTER =
{ 0x4D36E966, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } };

// Copy from HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\DeviceClasses
static const GUID GUID_DEVINTERFACE_LIST[] =
{
    // GUID_DEVINTERFACE_HID, 
    { 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DEVICECHANGE)
    {
        if ((DWORD)wParam == DBT_DEVNODES_CHANGED)
        {
            CheckHMDConnectState(VendorID, ProductID);
            ClearFlag = 0;
            //printf("Message : DBT_DEVNODES_CHANGED\n");		
        }
        return TRUE;
    }
    else return DefWindowProc(hWnd, message, wParam, lParam);
}
bool ReceiveMessage(int Massage)
{	
	if (((int)SelectMessage[0]) == Massage)
	{
		AAS = FALSE;
		return TRUE;
	}
	return FALSE;
}

bool InitializeHMDManager()
{
    return true;
}
bool FreeHMDManager()
{
    if (DeviceHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(DeviceHandle);
    }

    return true;
}
void RegisterForDeviceNotifications()
{

    // Request to receive messages when a device is attached or removed.
    // Also see WM_DEVICECHANGE in BEGIN_MESSAGE_MAP(CUsbhidiocDlg, CDialog).

    DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;
    HDEVNOTIFY DeviceNotificationHandle;

    DevBroadcastDeviceInterface.dbcc_size = sizeof(DevBroadcastDeviceInterface);
    DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    DevBroadcastDeviceInterface.dbcc_classguid = MyHidGuid;

    //	DeviceNotificationHandle =
    //		RegisterDeviceNotification(m_hWnd, &DevBroadcastDeviceInterface, DEVICE_NOTIFY_WINDOW_HANDLE);

}


bool CheckHMDConnectState(int VendorID, int ProductID)
{
    //Use a series of API calls to find a HID with a specified Vendor IF and Product ID.
    HIDD_ATTRIBUTES						Attributes;

    SP_DEVICE_INTERFACE_DATA			devInfoData;
    bool								LastDevice = FALSE;
    int									MemberIndex = 0;
    LONG								Result;
    char*								UsageDescription;
    HIDP_CAPS							Capabilities;
    PHIDP_PREPARSED_DATA	            PreparsedData;
    Length = 0;
    detailData = NULL;
    DeviceHandle = NULL;

    /*
    API function: HidD_GetHidGuid
    Get the GUID for all system HIDs.
    Returns: the GUID in MyHidGuid.
    */

    HidD_GetHidGuid(&MyHidGuid);

    /*
    API function: SetupDiGetClassDevs
    Returns: a handle to a device information set for all installed devices.
    Requires: the GUID returned by GetHidGuid.
    */

    hDevInfo = SetupDiGetClassDevs
        (&MyHidGuid,
        NULL,
        NULL,
        DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

    devInfoData.cbSize = sizeof(devInfoData);

    //Step through the available devices looking for the one we want. 
    //Quit on detecting the desired device or checking all available devices without success.

    MemberIndex = 0;
    LastDevice = FALSE;

    do
    {
        /*
        API function: SetupDiEnumDeviceInterfaces
        On return, MyDeviceInterfaceData contains the handle to a
        SP_DEVICE_INTERFACE_DATA structure for a detected device.
        Requires:
        The DeviceInfoSet returned in SetupDiGetClassDevs.
        The MyHidGuid returned in GetHidGuid.
        An index to specify a device.
        */

        Result = SetupDiEnumDeviceInterfaces
            (hDevInfo,
            0,
            &MyHidGuid,
            MemberIndex,
            &devInfoData);

        if (Result != 0)
        {
            //A device has been detected, so get more information about it.

            /*
            API function: SetupDiGetDeviceInterfaceDetail
            Returns: an SP_DEVICE_INTERFACE_DETAIL_DATA structure
            containing information about a device.
            To retrieve the information, call this function twice.
            The first time returns the size of the structure in Length.
            The second time returns a pointer to the data in DeviceInfoSet.
            Requires:
            A DeviceInfoSet returned by SetupDiGetClassDevs
            The SP_DEVICE_INTERFACE_DATA structure returned by SetupDiEnumDeviceInterfaces.

            The final parameter is an optional pointer to an SP_DEV_INFO_DATA structure.
            This application doesn't retrieve or use the structure.
            If retrieving the structure, set
            MyDeviceInfoData.cbSize = length of MyDeviceInfoData.
            and pass the structure's address.
            */

            //Get the Length value.
            //The call will return with a "buffer too small" error which can be ignored.

            Result = SetupDiGetDeviceInterfaceDetail
                (hDevInfo,
                &devInfoData,
                NULL,
                0,
                &Length,
                NULL);

            //Allocate memory for the hDevInfo structure, using the returned Length.

            detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);

            //Set cbSize in the detailData structure.

            detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

            //Call the function again, this time passing it the returned buffer size.

            Result = SetupDiGetDeviceInterfaceDetail
                (hDevInfo,
                &devInfoData,
                detailData,
                Length,
                &Required,
                NULL);

            // Open a handle to the device.
            // To enable retrieving information about a system mouse or keyboard,
            // don't request Read or Write access for this handle.

            /*
            API function: CreateFile
            Returns: a handle that enables reading and writing to the device.
            Requires:
            The DevicePath in the detailData structure
            returned by SetupDiGetDeviceInterfaceDetail.
            */

            DeviceHandle = HIDSIM_CreateHIDFile(detailData->DevicePath);

            /*
            API function: HidD_GetAttributes
            Requests information from the device.
            Requires: the handle returned by CreateFile.
            Returns: a HIDD_ATTRIBUTES structure containing
            the Vendor ID, Product ID, and Product Version Number.
            Use this information to decide if the detected device is
            the one we're looking for.
            */

            //Set the Size to the number of bytes in the structure.

            Attributes.Size = sizeof(Attributes);

            Result = HidD_GetAttributes
                (DeviceHandle,
                &Attributes);



            //Is it the desired device?

            MyDeviceDetected = FALSE;


            if (Attributes.VendorID == VendorID)
            {
                if (Attributes.ProductID == ProductID)
                {
                    //Both the Vendor ID and Product ID match.

                    MyDeviceDetected = TRUE;
                    MyDevicePathName = detailData->DevicePath;


                    //Register to receive device notifications.

                    //RegisterForDeviceNotifications();

                    //Get the device's capablities.
                    //HIDDeviceDesc* desc = new HIDDeviceDesc();
                    //HIDSIM_initUsage(DeviceHandle, desc);

                    HidD_GetPreparsedData
                        (DeviceHandle,
                        &PreparsedData);

                    HidP_GetCaps
                        (PreparsedData,
                        &Capabilities);

                    ReadHandle = CreateFile
                        (detailData->DevicePath,
                        GENERIC_READ,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        (LPSECURITY_ATTRIBUTES)NULL,
                        OPEN_EXISTING,
                        FILE_FLAG_OVERLAPPED,
                        NULL);





                } //if (Attributes.ProductID == ProductID)
                else
                    //The Product ID doesn't match.
                    CloseHandle(DeviceHandle);

            } //if (Attributes.VendorID == VendorID)
            else
                //The Vendor ID doesn't match.
                CloseHandle(DeviceHandle);

            //Free the memory used by the detailData structure (no longer needed).

            free(detailData);

        }  //if (Result != 0)
        else
            //SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.
            LastDevice = TRUE;

        //If we haven't found the device yet, and haven't tried every available device,
        //try the next one.
        MemberIndex = MemberIndex + 1;

    } //do
    while ((LastDevice == FALSE) && (MyDeviceDetected == FALSE));


    //Free the memory reserved for hDevInfo by SetupDiClassDevs.
    SetupDiDestroyDeviceInfoList(hDevInfo);
    return MyDeviceDetected;
}

bool ReadDiviceHandle(UCHAR* Report)
{
    if (INVALID_HANDLE_VALUE != DeviceHandle)
    {
        ReadFile
            (ReadHandle,
            Report,
            8,
            &NumberOfBytesRead,
            (LPOVERLAPPED)&HIDOverlapped);
        return true;
    }
    return false;
}

bool GetSelectMessage(UCHAR* SelectMessage)
{
    if (INVALID_HANDLE_VALUE != DeviceHandle)
    {
        UCHAR aBuf[FEATURE_IAP_SIZE] = { 0 };
        bool bRet = FALSE;
        aBuf[0] = FEATURE_SELECTMESSAGE;
        bRet = HidD_GetFeature(DeviceHandle, aBuf, FEATURE_MODE_SIZE);
        SelectMessage[0] = aBuf[3];
        return bRet;
    }
    return false;
}
bool SetSelectMessage(UCHAR SelectMessage)
{
    if (INVALID_HANDLE_VALUE != DeviceHandle)
    {
        UCHAR aBuf[FEATURE_IAP_SIZE] = { 0 };
        bool bRet = FALSE;
        aBuf[0] = FEATURE_SELECTMESSAGE;
        aBuf[3] = SelectMessage;
        bRet = HidD_SetFeature(DeviceHandle, aBuf, FEATURE_MODE_SIZE);
        return bRet;
    }
    return false;
}
bool GetLedMode(UCHAR* LedMode)
{
    UCHAR i;
    if (INVALID_HANDLE_VALUE != DeviceHandle)
    {
        UCHAR aBuf[FEATURE_IAP_SIZE] = { 0 };
        bool bRet = FALSE;
        aBuf[0] = FEATURE_LEDMODE;

        bRet = HidD_GetFeature(DeviceHandle, aBuf, FEATURE_LEDMODE_SIZE);
        //	LedMode[0] = aBuf[3];
        for (i = 0; i < 17; i++)
            LedMode[i] = aBuf[i];
        return bRet;
    }
    return false;
}

bool GetLedErrorid(UCHAR* ErrorMode)
{
    UCHAR i;
    if (INVALID_HANDLE_VALUE != DeviceHandle)
    {
        UCHAR aBuf[FEATURE_IAP_SIZE] = { 0 };
        bool bRet = FALSE;
        aBuf[0] = ERROR_ID;

        bRet = HidD_GetFeature(DeviceHandle, aBuf, FEATURE_ERRORMODE_SIZE);
        //	LedMode[0] = aBuf[3];
        ErrorMode[0] = aBuf[3];
        return bRet;
    }
    return false;
}

bool SetLedMode(UCHAR* LedMode)
{
    UCHAR i;
    if (INVALID_HANDLE_VALUE != DeviceHandle)
    {
        UCHAR aBuf[FEATURE_IAP_SIZE] = { 0 };
        bool bRet = FALSE;
        aBuf[0] = FEATURE_LEDMODE;
        //	aBuf[3] = LedMode;
        for (i = 0; i < 17; i++)
        {
            aBuf[i] = LedMode[i];
        }
        bRet = HidD_SetFeature(DeviceHandle, aBuf, FEATURE_LEDMODE_SIZE);

        return bRet;
    }
    return false;
}

bool InputPulse(InputPulseHandler iph) //主函数。接收底层传上来的投币帧编号、钱币数、错误代码，将灯光数据再发送给底层；将投币帧编号、钱币数、错误代码发送给顶层；

{
	bool SendMessageFlag = FALSE; //给顶层和底层传数据标志位；
	UCHAR Report[64] = { 0 };  //接收底层传上来的数据数组；
	UCHAR m = 0;			 //表示向底层发送的第几次灯光数组；
	bool LED_FLAG = FALSE;  //灯光数组发送标志位；
	bool over_flag = FALSE;
	MSG msg;
	int   itemp;
	int TimerCount = 0;	 //定时器计数；当它等于4的时候，将给顶层和底层传数据标志位置1；
	SelectMessage[0] = 0; //初始化投币帧编号；
	SelectMessage[1] = 0;  //初始化错误代码；
//	coin = 0;   //初始化钱币数；
//	AAS = FALSE;    //初始化给顶层重复发数据标志位，当AAS =TRUE时，使能给顶层重复发数据标志位。
//	WNDCLASS wndClass;
////	ZeroMemory(&wndClass, sizeof(wndClass));
//	wndClass.lpszClassName = TEXT("myusbmsg");
//	wndClass.lpfnWndProc = WndProc;

	//RegisterClass(&wndClass);
	//HWND hWnd = CreateWindow(TEXT("myusbmsg"), TEXT(""), 0, 0, 0, 0, 0, 0, 0, GetModuleHandle(0), 0);
//	TimerId = SetTimer(NULL, 1, 500, NULL);
	connect_flag = CheckHMDConnectState(VendorID, ProductID);

//	SetSelectMessage(SelectMessage[0]);
	while (1)
	{	
		while (connect_flag == FALSE)    //当USB转接板的USB线拔掉后，程序会停在这个位置。直到USB线再次插上；
		{
			connect_flag = CheckHMDConnectState(VendorID, ProductID);
			Sleep(1000);
		}

		if (ReadDiviceHandle(Report))  //读底层传送上来的帧数据；
		{
		 if (Report[3] > SelectMessage[0] )	
			{
				ClearFlag = FALSE;
				SendMessageFlag = TRUE; //打开发送投币数据标志位
				SelectMessage[0] = Report[3]; //将底层传送上来的投币编号赋值给数组第0位
			//	coin = Report[4];  //将底层传送上来的投币钱数赋值给coin
			//	iph(SelectMessage[0]);
			//	printf("key:%03d\n", SelectMessage[0]);
				Report[3] = 0;
				SelectMessage[0] = 0;
				SetSelectMessage(SelectMessage[0]);
				over_flag = TRUE;
			}
		 if (Report[3] == 0 && (over_flag == TRUE))
		 {
			 over_flag = FALSE;
			 SelectMessage[0] = Report[3];
			 //	iph(SelectMessage[0]);
		     // printf("key:%03d\n", SelectMessage[0]);
			 iph(SelectMessage[0]);
		  }
		}
	}
	return true;
}