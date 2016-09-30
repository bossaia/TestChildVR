#include "HidDevice.h"
#include "stdio.h"


GUID    g_HidGuid;

HANDLE HIDSIM_CreateHIDFile(const char* path/*, bool exclusiveAccess*/) //const
{
	return ::CreateFile(path,0,FILE_SHARE_READ | FILE_SHARE_WRITE,(LPSECURITY_ATTRIBUTES)NULL,
		OPEN_EXISTING,0,NULL);
}


bool HIDSIM_GetHMDProductInfo(HANDLE hidDev, HIDDeviceDesc* desc) //const
{
	HIDD_ATTRIBUTES attr;
	attr.Size = sizeof(attr);
	if (!HidD_GetAttributes(hidDev, &attr)) {
		//		DWORD dw = GetLastError();
		return false;
	}

	desc->VendorId = attr.VendorID;
	desc->ProductId = attr.ProductID;
	desc->VersionNumber = attr.VersionNumber;
	return true;
}

BOOLEAN HIDSIM_GetFeatureDfu(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	BOOLEAN bRet = FALSE;

	aBuf[0] = FEATURE_DFU;

	bRet = HidD_GetFeature(hidDev, aBuf, FEATURE_DFU_SIZE);
	if (FALSE == bRet) {
		aBuf[0] = FEATURE_DFU_OC;
		bRet = HidD_GetFeature(hidDev, aBuf, FEATURE_DFU_SIZE);
	}
	return bRet;
}

BOOLEAN HIDSIM_SetFeatureDfu(HANDLE hidDev, BOOL bEnable)
{
	BOOLEAN bRet = FALSE;
	UCHAR aBuf[FEATURE_DFU_SIZE] = { 0 };

	aBuf[0] = FEATURE_DFU;
	aBuf[1] = 0x01;
	aBuf[2] = 0x00;
	aBuf[3] = bEnable ? 0x01 : 0x00;

	bRet = HidD_SetFeature(hidDev, aBuf, sizeof(aBuf));
	if (FALSE == bRet) {
		aBuf[0] = FEATURE_DFU_OC;
		bRet = HidD_SetFeature(hidDev, aBuf, sizeof(aBuf));
	}

	return bRet;
}

BOOLEAN HIDSIM_GetFeatureMode(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	BOOLEAN bRet = FALSE;

	aBuf[0] = FEATURE_MODE;

	bRet = HidD_GetFeature(hidDev, aBuf, FEATURE_MODE_SIZE);

	return bRet;
}

BOOLEAN HIDSIM_SetFeatureMode(HANDLE hidDev, UCHAR uMode)
{
	UCHAR aBuf[FEATURE_MODE_SIZE] = { 0 };

	aBuf[0] = FEATURE_MODE;
	aBuf[1] = 0x01;
	aBuf[2] = 0x00;
	aBuf[3] = uMode;

	return HidD_SetFeature(hidDev, aBuf, sizeof(aBuf));
}

BOOLEAN HIDSIM_GetFeatureBright(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	BOOLEAN bRet = FALSE;

	aBuf[0] = FEATURE_BRIGHT;

	bRet = HidD_GetFeature(hidDev, aBuf, FEATURE_MODE_SIZE);

	return bRet;
}



BOOLEAN HIDSIM_SetFeatureBright(HANDLE hidDev, UCHAR NUM)
{
	UCHAR aBuf[FEATURE_MODE_SIZE] = { 0 };

	aBuf[0] = FEATURE_BRIGHT;
	aBuf[1] = 0x01;
	aBuf[2] = 0x00;
	aBuf[3] = NUM;

	return HidD_SetFeature(hidDev, aBuf, sizeof(aBuf));
}

BOOLEAN HIDSIM_SetFeatureConfig(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	UCHAR aBuf[FEATURE_CONFIG_SIZE] = {0};

	return HidD_SetFeature(hidDev, aBuf, FEATURE_CONFIG_SIZE);
}

BOOLEAN HIDSIM_GetFeatureConfig(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_CONFIG_SIZE] = {0};

	aBuf[0] = FEATURE_CONFIG;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_CONFIG_SIZE);
}

BOOLEAN HIDSIM_GetFeatureCalibrete(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_CALIBRATE_SIZE] = {0};

	aBuf[0] = FEATURE_CALIBRATE;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_CALIBRATE_SIZE);
}

BOOLEAN HIDSIM_SetFeatureCalibrete(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_CALIBRATE_SIZE] = {0};

	//	aBuf[0] = FEATURE_CALIBRATE;

	return HidD_SetFeature(hidDev, aBuf, FEATURE_CALIBRATE_SIZE);
}

BOOLEAN HIDSIM_GetFeatureRange(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_RANGE_SIZE] = {0};

	aBuf[0] = FEATURE_RANGE;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_RANGE_SIZE);
}

BOOLEAN HIDSIM_SetFeatureRange(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_RANGE_SIZE] = {0};

	//	aBuf[0] = FEATURE_RANGE;

	return HidD_SetFeature(hidDev, aBuf, FEATURE_RANGE_SIZE);
}

BOOLEAN HIDSIM_GetFeatureRegister(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_REGISTER_SIZE] = {0};

	aBuf[0] = FEATURE_REGISTER;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_REGISTER_SIZE);
}

BOOLEAN HIDSIM_SetFeatureRegister(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_REGISTER_SIZE] = {0};

	//	aBuf[0] = FEATURE_REGISTER;

	return HidD_SetFeature(hidDev, aBuf, FEATURE_REGISTER_SIZE);
}

BOOLEAN HIDSIM_GetFeatureGPIO(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_GPIO_SIZE] = {0};

	aBuf[0] = FEATURE_GPIO;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_GPIO_SIZE);
}

BOOLEAN HIDSIM_SetFeatureGPIO(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_GPIO_SIZE] = {0};

	//	aBuf[0] = FEATURE_GPIO;

	return HidD_SetFeature(hidDev, aBuf, FEATURE_GPIO_SIZE);
}

BOOLEAN HIDSIM_GetFeatureKeepAlive(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_KEEP_ALIVE_SIZE] = {0};

	aBuf[0] = FEATURE_KEEP_ALIVE;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_KEEP_ALIVE_SIZE);
}

BOOLEAN HIDSIM_SetFeatureKeepAlive(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_KEEP_ALIVE_SIZE] = {0};

	//	aBuf[0] = FEATURE_KEEP_ALIVE;

	return HidD_SetFeature(hidDev, aBuf, FEATURE_KEEP_ALIVE_SIZE);
}

BOOLEAN HIDSIM_GetFeatureDisplayInfo(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_DISPLAY_INFO_SIZE] = {0};

	aBuf[0] = FEATURE_DISPLAY_INFO;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_DISPLAY_INFO_SIZE);
}

BOOLEAN HIDSIM_SetFeatureDisplayInfo(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_DISPLAY_INFO_SIZE] = {0};

	//	aBuf[0] = FEATURE_DISPLAY_INFO;

	return HidD_SetFeature(hidDev, aBuf, FEATURE_DISPLAY_INFO_SIZE);
}

BOOLEAN HIDSIM_GetFeatureSerial(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_SERIAL_SIZE] = {0};

	aBuf[0] = FEATURE_SERIAL;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_SERIAL_SIZE);
}

BOOLEAN HIDSIM_SetFeatureSerial(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_SERIAL_SIZE] = {0};

	//	aBuf[0] = FEATURE_SERIAL;

	return HidD_SetFeature(hidDev, aBuf, FEATURE_SERIAL_SIZE);
}

BOOLEAN HIDSIM_GetFeatureIAP(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_IAP_SIZE] = {0};

	aBuf[0] = FEATURE_IAP;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_IAP_SIZE);
}

BOOLEAN HIDSIM_GetFeatureFwVer(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_IAP_SIZE] = {0};

	aBuf[0] = FEATURE_GET_FW_VER;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_GET_FW_VER_SIZE);
}

BOOLEAN HIDSIM_GetFeatureMcuId(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_IAP_SIZE] = {0};

	aBuf[0] = FEATURE_GET_MCU_ID;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_GET_MCU_ID_SIZE);
}

BOOLEAN HIDSIM_SetFeatureIAP(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_IAP_SIZE] = {0};

	//	aBuf[0] = FEATURE_IAP;

	return HidD_SetFeature(hidDev, aBuf, FEATURE_IAP_SIZE);
}

#if _DEBUG
BOOLEAN HIDSIM_GetFeatureDebug(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_DEBUG_SIZE] = {0};

	aBuf[0] = FEATURE_DEBUG;

	return HidD_GetFeature(hidDev, aBuf, FEATURE_DEBUG_SIZE);
}

BOOLEAN HIDSIM_SetFeatureDebug(HANDLE hidDev, UCHAR aBuf[], UINT nlen)
{
	//	CHAR aBuf[FEATURE_DEBUG_SIZE] = {0};

	aBuf[0] = FEATURE_DEBUG;

	return HidD_SetFeature(hidDev, aBuf, FEATURE_DEBUG_SIZE);
}
#endif

bool HIDSIM_initUsage(HANDLE hidDev, HIDDeviceDesc* desc) //const
{
	bool                 result = false;
	HIDP_CAPS            caps;
	PHIDP_PREPARSED_DATA preparsedData = 0;

	if (!HidD_GetPreparsedData(hidDev, &preparsedData))
		return false;

	if (HidP_GetCaps(preparsedData, &caps) == HIDP_STATUS_SUCCESS)
	{
		desc->Usage = caps.Usage;
		desc->UsagePage = caps.UsagePage;
		result = true;
	}
	HidD_FreePreparsedData(preparsedData);
	return result;
}

void HIDSIM_initStrings(HANDLE hidDev, HIDDeviceDesc* desc) //const
{
	// Documentation mentions 126 as being the max for USB.
	wchar_t strBuffer[196];

	// HidD_Get*String functions return nothing in buffer on failure,
	// so it's ok to do this without further error checking.
	strBuffer[0] = 0;
	HidD_GetManufacturerString(hidDev, strBuffer, sizeof(strBuffer));
	//    desc->Manufacturer = strBuffer;
	wcscpy(desc->Manufacturer, strBuffer);

	strBuffer[0] = 0;
	HidD_GetProductString(hidDev, strBuffer, sizeof(strBuffer));
	//    desc->Product = strBuffer;
	wcscpy(desc->Product, strBuffer);

	strBuffer[0] = 0;
	HidD_GetSerialNumberString(hidDev, strBuffer, sizeof(strBuffer));
	//    desc->SerialNumber = strBuffer;
	wcscpy(desc->SerialNumber, strBuffer);
}

bool HIDSIM_getFullDesc(HANDLE hidDev, HIDDeviceDesc* desc) //const
{

	if (!HIDSIM_GetHMDProductInfo(hidDev, desc))
	{
		return false;
	}

	if (!HIDSIM_initUsage(hidDev, desc))
	{
		return false;
	}

	HIDSIM_initStrings(hidDev, desc);

	return true;
}
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 255
#include <shlwapi.h>

CHAR* HIDSIM_GetHidDeviceWin32Path(CHAR *pHidGuid, WORD Vid, WORD Pid)
{
	CHAR *pStr = NULL;
	HKEY hKey;
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 

	DWORD i, retCode;

	static TCHAR  achValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;

	sprintf(achValue, "SYSTEM\\CurrentControlSet\\Control\\DeviceClasses\\{%s}", pHidGuid);
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		achValue,
		0,
		KEY_READ,
		&hKey) != ERROR_SUCCESS) {
		return pStr;
	}

	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		hKey,                    // key handle 
		achClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 
	// Enumerate the subkeys, until RegEnumKeyEx fails.    
	if (cSubKeys)
	{
		for (i = 0; i<cSubKeys; i++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
				sprintf(achValue, "#VID_%04x&PID_%04x#", Vid, Pid);
				if (StrStrI(achKey, achValue)) 
				{
					sprintf(achValue, "\\\\.\\%s", achKey + strlen("##?#"));
					HANDLE hHid = HIDSIM_CreateHIDFile(achValue);
					if (INVALID_HANDLE_VALUE != hHid) 
					{
						CloseHandle(hHid);

						pStr = achValue;
						break;
					}
				}
			}
		}
	}

	RegCloseKey(hKey);
	return pStr;
}

