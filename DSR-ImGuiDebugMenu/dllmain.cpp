//#include "dinput8.h"
//#include "d3d11hook.h"
#include "DSRDebugMenu.h"
#include "DbgSettings.h"
#include "Globals.h"
#include <locale.h>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <tchar.h>
#include <ctime>
//#include <iomanip>
//#include <sstream>

using namespace std;



DWORD64 bLoadParamdefbnd = 0;

tDirectInput8Create oDirectInput8Create;

unsigned int debugMem = 0x1000000;

HANDLE hProcessSHIT = NULL;
void PatchGame();

DWORD GetProcIdSHIT(const wchar_t* procname);
DWORD ConvertColor(float[4]);
LPVOID fuckshitshit = 0;
LPVOID haha = 0;
DWORD64 bGetCameraObj = 0;
DWORD64 bSetCameraObj = 0;
DWORD64 bGetCameraObjAlt = 0;
DWORD64 bLoadGameProperties = 0;
DWORD64 bLoadMsbNames = 0;
DWORD64 bDrawDebugMenuGOGOGO = 0;
DWORD64 bDebugMemAlloc = 0;
DWORD64 bWritePlayerName = 0;
DWORD64 bContinueInitPlayer = 0x14031C6D1;
DWORD64 bCheckDebugDash = 0;
DWORD64 bApplySettingsDamageMan = 0;
DWORD64 bApplySettingsWorldChrManDbg = 0;
DWORD64 bFreeCam = 0;
DWORD64 bGetFreeCamMode1 = 0;
DWORD64 bGetFreeCamMode2 = 0;
DWORD64 bGetFreeCamMode3 = 0;
DWORD64 bGetFreeCamMode4 = 0;
DWORD64 bExitButtonComboCheck1 = 0;
DWORD64 bExitButtonComboCheck2 = 0;
DWORD64 bExitButtonComboCheck3 = 0;
DWORD64 bLoadGamePropertiesOrSth = 0;
DWORD64 bLoadDbgMenuTextHighlightColor = 0;

DWORD64 bOpenLogConsole = 0;
BOOL g_isOpenConsole = 0;

DWORD64 bEzDrawAddDrawPlans1 = 0;
DWORD64 bEzDrawAddDrawPlans2 = 0;
DWORD64 bEzDrawAddDrawPlans3 = 0;
DWORD64 bEzDrawAddDrawPlans4 = 0;
DWORD64 bEzDrawAddDrawPlans5 = 0;
DWORD64 bEzDrawAddDrawPlans6 = 0;
//DWORD64 fLoadGameProperties = 0;

DWORD64 bRemoAddTest = 0;
DWORD64 bAddUnderConstructionParamMan = 0;
DWORD64 bAddUnderConstructionEmevdMan = 0;

DWORD64 bAntiTamperSkip = 0;
static void InitUnhandledExceptionFilter();
DWORD textHighlightColor = 0xFFC0FF80;
int g_dbgMenuWidth = 450;
int g_dbgMenuHeight = 600;
int g_dbgMenuPosX = 25;
int g_dbgMenuPosY = 25;

float g_DbgConsolePosX = 800.f;
float g_DbgConsolePosY = 100.f;
float g_DbgConsoleSizeX = 520.f;
float g_DbgConsoleSizeY = 600.f;

bool g_isDisableMouse = false;

DamageManSettings damageManSettings;
DbgMenuSettings dbgMenuSettings;
WorldChrManDbgSettings worldChrManDbgSettings;

DWORD64 pSettingsDamageMan = (DWORD64)&damageManSettings;
DWORD64 pSettingsDbgMenu = (DWORD64)&dbgMenuSettings;
DWORD64 pSettingsWorldChrManDbg = (DWORD64)&worldChrManDbgSettings;


const LPCWSTR AppWindowTitle = L"DARK SOULS™: REMASTERED"; // Targeted D11 Application Window Title.
//const LPCWSTR AppWindowTitle = L"DARK SOULS III";
HWND g_hWnd = NULL;
//AddressLookupTable<void> ProxyAddressLookupTable = AddressLookupTable<void>();
//
//DirectInput8CreateProc m_pDirectInput8Create;
//DllCanUnloadNowProc m_pDllCanUnloadNow;
//DllGetClassObjectProc m_pDllGetClassObject;
//DllRegisterServerProc m_pDllRegisterServer;
//DllUnregisterServerProc m_pDllUnregisterServer;
//GetdfDIJoystickProc m_pGetdfDIJoystick;

BYTE debugdashenable_patch = 1;
BYTE gesturecombo_patch = 0x74;
DWORD luamem_patch = 0x9C4000;
BYTE blendstate_patch = 3;
BYTE patching_system[2] = { 0xB0, 0x01 };
BYTE boot_patch[4] = { 0x55, 0x67, 0xFE, 0xFF };
BYTE dbg_patch[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
BYTE navi_patch[6] = { 0xE9, 0xA5, 0x05, 0x00, 0x00, 0x90 };
BYTE navi_patch2[9] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
BYTE navi_patch3[8] = { 0xE9, 0x86, 0x0D, 0x00, 0x00, 0x90, 0x90, 0x90 };
BYTE we_patch[10] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

uint64_t dbgMenuControlVtableOffsets[106] = { 0x1412A9778, 0x1412A9820, 0x1412A9AA8, 0x1412A9C18, 0x1412A9DB0, 0x1412ADD58, 0x1412CE328, 0x1412CE3A8, 0x1412D19C8, 0x141309BC8, 0x141312D18, 0x141313D50, 0x141314710, 
											  0x141314E40, 0x141314EC0, 0x1413160B0, 0x14131A020, 0x14131E958, 0x141335A78, 0x141335D18, 0x1413367B0, 0x141336B68, 0x141337268, 0x141337740, 0x1413386E0, 0x141340508,
											  0x1413465F8, 0x141349A78, 0x141349B08, 0x141362DB8, 0x1413650A0, 0x141365120, 0x1413651A0, 0x14136C588, 0x14136D2B0, 0x14136D598, 0x14136DA08, 0x14136DF50, 0x14137D168,
											  0x14138BE68, 0x141390FD0, 0x141398E18, 0x1413D0BB8, 0x1413DE948, 0x1413E0530, 0x1413E0778, 0x1413E0BB0, 0x1413E0FC0, 0x1413E1A38, 0x1413E1FD8, 0x1413E34A0, 0x1413E4208,
											  0x1413E4B88, 0x1413E59E0, 0x1413E5F78, 0x1413E6DD8, 0x1413E73D0, 0x1413E77B0, 0x1413E8438, 0x1413E8718, 0x1413F3388, 0x1413F3E68, 0x1413F41D0, 0x1413F4BF0, 0x1413F4F80,
											  0x1413F53F0, 0x1413F5A48, 0x1413F69E0, 0x1413F6F50, 0x1413F7240, 0x1413F74D0, 0x1413F76C8, 0x1413F7938, 0x1413F7CC8, 0x1413F7ED0, 0x1413F8190, 0x1413F83C0, 0x1413F8630,
											  0x1413F88E8, 0x1413F8B58, 0x1413F8CF0, 0x1413F8EE8, 0x1413F9128, 0x1413F9318, 0x1413F9550, 0x1413F99E8, 0x1413F9BD0, 0x1413F9DF0, 0x1413FA068, 0x1413FA2B0, 0x1413FA508,
											  0x1413FA760, 0x1413FA9F8, 0x1413FAC98, 0x1413FAF00, 0x1413FB2A0, 0x1413FB4F0, 0x1413FB758, 0x1413FB958, 0x1413FBB30, 0x1413FBD18, 0x1413FBF40, 0x1413FC168, 0x1413FC330,
											  0x1413FC728, 0x1413FC920 };
	
										/*0x1412A9780, 0x1412A9828, 0x1412A9AB0, 0x1412A9C20, 0x1412A9DB8, 0x1412ADD60, 0x1412CE330, 0x1412CE3B0, 0x1412D19D0, 0x141309BD0, 0x141312D20, 0x141313D58, 0x141314718,
									  0x141314E48, 0x141314EC8, 0x1413160B8, 0x14131A028, 0x14131E960, 0x141335A80, 0x141335D20, 0x1413367B8, 0x141336B70, 0x141337270, 0x141337748, 0x1413386E8, 0x141340510,
									  0x14136C590, 0x14136D2B8, 0x14136DA10, 0x14137D170, 0x14138BE70, 0x141398E20, 0x1413E1FE0, 0x1413E77B8, 0x1413F3390, 0x1413F41D8, 0x1413F4BF8, 0x1413F7940, 0x1413F7CD0,
									  0x1413F83C8, 0x1413F8638, 0x1413F9558, 0x1413FA768, 0x1413FAA00, 0x1413FACA0, 0x1413FAF08, 0x1413FB2A8, 0x1413FB4F8, 0x1413FB760, 0x1413FB960, 0x1413FBB38, 0x1413FBD20,
									  0x1413FBF48, 0x1413FC170, 0x1413FC338, 0x1413FC730, 0x1413FC928 };*/


BYTE getDbgMenuLabelNodeFunc[20] = { 0x48, 0xA1, 0xC8, 0x4C, 0xC0, 0x41, 0x01, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC0, 0x74, 0x03, 0x48, 0x8B, 0x40, 0x08, 0xC3 };

uint64_t getDbgMenuLabelNodeFuncCalls[26] = { 0x1400F7EE6, 0x14015B127, 0x14015B131, 0x14015C134, 0x14015C13E, 0x140257786, 0x140257797, 0x140257DF1, 0x140257DFF, 0x1402C34EA, 0x1402C34F8, 0x14044B85B, 
											  0x14044B869, 0x140516A3B, 0x140516A45, 0x140516AFA, 0x140516B04, 0x14059FD85, 0x14059FD93, 0x140779CA5, 0x140779CB3, 0x1407E7F8B, 0x1407ED21E, 0x1407F5A15,
											  0x1407F5A23, 0x1407F61D5 };
BYTE getDbgMenuLabelNodeFuncCallsLastByte[26] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//wulf2k's patch relocated
BYTE initDbgMenuPatchJump[5] = { 0xE9, 0x06, 0x22, 0x79, 0x00 };

BYTE initDbgMenuPatch[30] = { 0x48, 0x8D, 0x0D, 0x26, 0x81, 0xBC, 0x00, 0xE8, 0x51, 0x1E, 0xB8, 0xFF, 0x48, 0x8B, 0x0D, 0x72, 0x00, 0x32, 0x01, 0x48, 0x89, 0x41, 0x08, 0x48, 0x83, 0xC4, 0x28, 0xC3, 0x90, 0x90 };

BYTE fullCircleUTF16[4] = { 0xCF, 0x25, 0x00, 0x00 };
BYTE emptyCircleUTF16[4] = { 0xCB, 0x25, 0x00, 0x00 };

BYTE gestureMenuPatch[32] = { 0x48, 0x8B, 0x4B, 0x08, 0xBA, 0x44, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x7C, 0x24, 0x40, 0x0F, 0x28, 0x74, 0x24, 0x20, 0x48, 0x83, 0xC4, 0x30, 0x5B, 0xE9, 0x4A, 0x0F, 0x00, 0x00, 0x90, 0x90, 0x90 };

BYTE backgroundPatch[7] = { 0x0F, 0x28, 0x35, 0xEE, 0x1B, 0x19, 0x01 };

BYTE freeCamPatch[6] = { 0xE9, 0x04, 0x01, 0x00, 0x00, 0x90 };

BYTE dbgCamZSpeedPatch[4] = { 0xEA, 0xD7, 0x13, 0x01 };
BYTE dbgCamYSpeedPatch[4] = { 0xF0, 0xD5, 0x13, 0x01 };
BYTE dbgCamXSpeedPatch[4] = { 0xFA, 0xD6, 0x13, 0x01 };

BYTE frpgSystemAntiAntiCheatWhateverPatch[5] = { 0xC3, 0x90, 0x90, 0x90, 0x90 };

uint64_t returnZeroFunc = 0x140152AF0;

BYTE nop5Patch[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };



DWORD64 whatever;
DWORD64 fPatchGame = (DWORD64)&PatchGame;
DWORD64 fConvertColor = (DWORD64)&ConvertColor;
DWORD64 ffDbgDispLoading = (DWORD64)&fDbgDispLoading;
DWORD64 fPrintDbgLog = (DWORD64)&PrintDbgLog;
DWORD64 fPrintText = (DWORD64)&PrintText;

unsigned int ezDrawDbgMenuBufferSize = 0x3000;

vector<GamePatch> gamePatches = {
	{ COPY, (BYTE*)0x1420B52F0, (BYTE*)&returnZeroFunc, 8, NULL, NULL },
	{ COPY, (BYTE*)0x14015E33B, backgroundPatch, 7, NULL, NULL },
	{ HOOK, (BYTE*)0x140152A38, NULL, 0, (LPVOID)fInitRootDbgMenuLabelNode, NULL },
	{ COPY, (BYTE*)0x14015E594, (BYTE*)&ezDrawDbgMenuBufferSize, 4, NULL, NULL },
	{ HOOK, (BYTE*)0x1401B67F3, NULL, 7, (LPVOID)tLoadGamePropertiesOrSth, &bLoadGamePropertiesOrSth },
	//{ HOOK, (BYTE*)0x14025E10B, NULL, 7, (LPVOID)LoadGameProperties, &bLoadGameProperties },
	{ HOOK, (BYTE*)0x1403CB254, NULL, 7, (LPVOID)tApplySettingsDamageMan, &bApplySettingsDamageMan },
	{ HOOK, (BYTE*)0x1403913ED, NULL, 0, (LPVOID)tEsdDbgLogOutput, NULL },
	{ COPY, (BYTE*)0x141ACCC18, (BYTE*)fPrintText, 8, NULL, NULL },
	{ HOOK, (BYTE*)0x14047BB44, NULL, 5, (LPVOID)tLoadDbgMenuTextHighlightColor, &bLoadDbgMenuTextHighlightColor },
	{ COPY, (BYTE*)0x1402773F7, boot_patch, 4, NULL, NULL },
	{ COPY, (BYTE*)0x1401E8EBF, (BYTE*)&blendstate_patch, 1, NULL, NULL },
	{ HOOK, (BYTE*)0x140522043, NULL, 6, (LPVOID)fAddUnderConstructionParamMan, &bAddUnderConstructionParamMan },
	{ HOOK, (BYTE*)0x1407C3576, NULL, 10, (LPVOID)fAddUnderConstructionEmevdMan, &bAddUnderConstructionEmevdMan },
	{ HOOK, (BYTE*)0x1432AEAB8, NULL, 0, (LPVOID)loadEnemyMsbName, NULL },
	{ HOOK, (BYTE*)0x140175075, NULL, 6, (LPVOID)writePlayerName, &bWritePlayerName },
	{ HOOK, (BYTE*)0x1422847E1, NULL, 0, (LPVOID)freeEnemyMsbName, NULL },
	{ HOOK, (BYTE*)0x14015BE2A, NULL, 10, (LPVOID)tDrawDebugMenuGOGOGO, &bDrawDebugMenuGOGOGO },
	{ COPY, (BYTE*)0x14131D2A0, fullCircleUTF16, 4, NULL, NULL },
	{ COPY, (BYTE*)0x14131C668, emptyCircleUTF16, 4, NULL, NULL },
	{ HOOK, (BYTE*)0x140370122, NULL, 5, (LPVOID)tCheckDebugDash, &bCheckDebugDash },
	{ COPY, (BYTE*)0x141D151DA, &debugdashenable_patch, 1, NULL, NULL },
	{ COPY, (BYTE*)0x141AC56D8, (BYTE*)&ffDbgDispLoading, 8, NULL, NULL },
	{ HOOK, (BYTE*)0x1402CD384, NULL, 8, (LPVOID)tEzDrawAddDrawPlans1, &bEzDrawAddDrawPlans1 },
	{ HOOK, (BYTE*)0x1402CD626, NULL, 8, (LPVOID)tEzDrawAddDrawPlans2, &bEzDrawAddDrawPlans2 },
	{ HOOK, (BYTE*)0x1402CD851, NULL, 8, (LPVOID)tEzDrawAddDrawPlans3, &bEzDrawAddDrawPlans3 },
	{ HOOK, (BYTE*)0x1402CDAE7, NULL, 8, (LPVOID)tEzDrawAddDrawPlans4, &bEzDrawAddDrawPlans4 },
	{ HOOK, (BYTE*)0x1402CDD92, NULL, 8, (LPVOID)tEzDrawAddDrawPlans5, &bEzDrawAddDrawPlans5 },
	{ HOOK, (BYTE*)0x1402CF099, NULL, 5, (LPVOID)tEzDrawAddDrawPlans6, &bEzDrawAddDrawPlans6 },
	{ COPY, (BYTE*)0x1404FA954, dbg_patch, 6, NULL, NULL },
	{ HOOK, (BYTE*)0x14024DF91, NULL, 7, (LPVOID)fFreeCam, &bFreeCam },
	{ HOOK, (BYTE*)0x14024B07B, NULL, 5, (LPVOID)tExitButtonComboCheck1, &bExitButtonComboCheck1 },
	{ HOOK, (BYTE*)0x14025622C, NULL, 5, (LPVOID)tExitButtonComboCheck2, &bExitButtonComboCheck2 },
	{ HOOK, (BYTE*)0x14027AF42, NULL, 5, (LPVOID)tExitButtonComboCheck3, &bExitButtonComboCheck3 },
	{ COPY, (BYTE*)0x14019C1F2, dbgCamZSpeedPatch, 4, NULL, NULL },
	{ COPY, (BYTE*)0x14019C3EC, dbgCamYSpeedPatch, 4, NULL, NULL },
	{ COPY, (BYTE*)0x14019C2E2, dbgCamXSpeedPatch, 4, NULL, NULL },
	{ COPY, (BYTE*)0x1401A3435, &gesturecombo_patch, 1, NULL, NULL },
	{ COPY, (BYTE*)0x1401A3447, &gesturecombo_patch, 1, NULL, NULL },
	{ COPY, (BYTE*)0x1401A3449, gestureMenuPatch, 32, NULL, NULL },
	{ COPY, (BYTE*)0x14015AF49, frpgSystemAntiAntiCheatWhateverPatch, 5, NULL, NULL },
	{ COPY, (BYTE*)0x14015BEC7, nop5Patch, 5, NULL, NULL } //this mofo used to shred perfectly fine code
};

//load game.properties
	//hookLength = 7;
	//hookAddress = 0x14025E10B;
	//bLoadGameProperties = hookAddress + hookLength;
	////fLoadGameProperties = (DWORD64)(LPVOID)LoadGameProperties;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)tLoadGameProperties, 0);
	//MH_EnableHook((LPVOID)hookAddress);

inline void ProcessPatch(GamePatch* patch)
{
	DWORD oldProtect;

	if (patch->type == COPY)
	{
		VirtualProtect((LPVOID)patch->address, patch->numBytes, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((LPVOID)patch->address, (LPVOID)patch->bytes, patch->numBytes);
		VirtualProtect((LPVOID)patch->address, patch->numBytes, oldProtect, &oldProtect);
	}
	else 
	{
		if (patch->numBytes)
			*patch->pReturn = (DWORD64)patch->address + patch->numBytes;
		MH_CreateHook((LPVOID)patch->address, patch->pFunction, 0);
		MH_EnableHook((LPVOID)patch->address);
	}
}

char* GetFormattedTime(char* buf)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buf, 20, "%H:%M:%S", timeinfo);

	return buf;
}

VOID PrintDbgLog(wchar_t* format, char* args, byte* chrPtr)
{
	wchar_t buffer[256];
	char nameBuffer[64];
	char newbuf[1024];
	char newbuf2[1024];
	char timeBuf[20];
	vswprintf(buffer, 256, format, args);

	WideCharToMultiByte(CP_UTF8, 0, buffer, -1, newbuf, 1024, NULL, NULL);

	int stringLen = *(int*)(chrPtr + 0x510);
	byte* stringPos = chrPtr + 0x4F8;

	if (stringLen >= 8)
		stringPos = (byte*)*(uint64_t*)stringPos;

	WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)stringPos, -1, nameBuffer, 64, NULL, NULL);

	printf("%s: [ESD:%s] %s\n", GetFormattedTime(timeBuf), nameBuffer, newbuf);
}

//this is bad, change pls
void PrintText(DWORD64 ai, char* str)
{
	long long sthPtr = 0;

	ReadProcessMemory(hProcessSHIT, (LPVOID)(ai + 8), &sthPtr, 8, NULL);

	if (sthPtr)
	{
		ReadProcessMemory(hProcessSHIT, (LPVOID)sthPtr, &sthPtr, 8, NULL);

		if (sthPtr)
		{
			long long chrCtrl = 0;

			ReadProcessMemory(hProcessSHIT, (LPVOID)(sthPtr + 0x10), &chrCtrl, 8, NULL);

			if (chrCtrl)
			{
				uint64_t chrIns = 0;

				if (chrCtrl)
				{
					ReadProcessMemory(hProcessSHIT, (LPVOID)(chrCtrl + 0x10), &chrIns, 8, NULL);

					int count = 0;
					char read_char;
					char chrName[32];
					char strNew[320];
					char timeBuf[20];
					int stringLen = 0;
					uint64_t stringPos = chrIns + 0x4F8;

					ReadProcessMemory(hProcessSHIT, (LPVOID)(chrIns + 0x510), &stringLen, 4, NULL);

					if (stringLen >= 8)
						ReadProcessMemory(hProcessSHIT, (LPVOID)(chrIns + 0x4F8), &stringPos, 8, NULL);

					do
					{
						ReadProcessMemory(hProcessSHIT, (LPVOID)(stringPos + count * 2), &read_char, 1, NULL);
						chrName[count] = read_char;
						count++;
					} while (read_char);

					printf("%s: [AI:%s] %s\n", GetFormattedTime(timeBuf), chrName, str);
				}
			}
		}
	}
}

void InitSettings()
{
	damageManSettings.debugBallDisplay = 0;
	damageManSettings.debugInfoDisp = 0;
	damageManSettings.damageAtkParamRef = 0;
	damageManSettings.damageWpnDmy = 0;

	dbgMenuSettings.windowPosX = 0.96f;
	dbgMenuSettings.windowPosY = 0.96f;
	dbgMenuSettings.windowSizeX = 512.f;
	dbgMenuSettings.windowSizeY = 512.f;
	dbgMenuSettings.windowScaleX = 0.8f;
	dbgMenuSettings.windowScaleY = 0.8f;
	dbgMenuSettings.windowColorR = 0.0f;
	dbgMenuSettings.windowColorG = 0.0f;
	dbgMenuSettings.windowColorB = 0.0f;
	dbgMenuSettings.windowColorA = 0.1f;
	dbgMenuSettings.activeWindowColorR = 0.0f;
	dbgMenuSettings.activeWindowColorG = 0.0f;
	dbgMenuSettings.activeWindowColorB = 0.0f;
	dbgMenuSettings.activeWindowColorA = 0.1f;
	dbgMenuSettings.textHighlightColorR = 0.5f;
	dbgMenuSettings.textHighlightColorG = 1.0f;
	dbgMenuSettings.textHighlightColorB = 0.75f;
	dbgMenuSettings.textHighlightColorA = 1.0f;
}

void LoadDamageManOptionSelection()
{
	bool dbgBallDisp = GetPrivateProfileInt(L"DamageMan", L"DebugBallDisplay", 0, L"./game.properties");
	bool dbgInfoDisp = GetPrivateProfileInt(L"DamageMan", L"DebugInfoDisplay", 0, L"./game.properties");
	bool damageWpnPoly = GetPrivateProfileInt(L"DamageMan", L"DamageWpnPoly", 0, L"./game.properties");
	bool damageAtkParamRef = GetPrivateProfileInt(L"DamageMan", L"DamageAtkParamRef", 0, L"./game.properties");

	damageManSettings.debugBallDisplay = dbgBallDisp;
	damageManSettings.debugInfoDisp = dbgInfoDisp;
	damageManSettings.damageWpnDmy = damageWpnPoly;
	damageManSettings.damageAtkParamRef = damageAtkParamRef;
}

void LoadDbgMenuSection()
{
	DWORD oldProtect;
	_locale_t locale = _create_locale(LC_NUMERIC, "en-US");
	wchar_t buffer[32];
	uint64_t* offset = 0;

	GetPrivateProfileString(L"DbgMenu", L"Def.WindowPos.X", L"96.0", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowPosX = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.WindowPos.Y", L"96.0", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowPosY = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.WindowSize.X", L"512.0", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowSizeX = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.WindowSize.Y", L"512.0", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowSizeY = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.WindowScale.X", L"1.0", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowScaleX = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.WindowScale.Y", L"1.0", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowScaleY = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.WindowColor.R", L"0", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowColorR = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.WindowColor.G", L"0", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowColorG = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.WindowColor.B", L"0", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowColorB = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.WindowColor.A", L"0.1", buffer, 32, L"./game.properties");
	dbgMenuSettings.windowColorA = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.ActiveWindowColor.R", L"0", buffer, 32, L"./game.properties");
	dbgMenuSettings.activeWindowColorR = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.ActiveWindowColor.G", L"0", buffer, 32, L"./game.properties");
	dbgMenuSettings.activeWindowColorG = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.ActiveWindowColor.B", L"0", buffer, 32, L"./game.properties");
	dbgMenuSettings.activeWindowColorB = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.ActiveWindowColor.A", L"0.1", buffer, 32, L"./game.properties");
	dbgMenuSettings.activeWindowColorA = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.TextHighlightColor.R", L"0.75", buffer, 32, L"./game.properties");
	dbgMenuSettings.textHighlightColorR = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.TextHighlightColor.G", L"1.0", buffer, 32, L"./game.properties");
	dbgMenuSettings.textHighlightColorG = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.TextHighlightColor.B", L"0.5", buffer, 32, L"./game.properties");
	dbgMenuSettings.textHighlightColorB = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgMenu", L"Def.TextHighlightColor.A", L"1.0", buffer, 32, L"./game.properties");
	dbgMenuSettings.textHighlightColorA = _wtof_l(buffer, locale);

	offset = (uint64_t*)0x14134D520;
	*(float*)offset = dbgMenuSettings.windowPosX;
	offset = (uint64_t*)0x14134D524;
	*(float*)offset = dbgMenuSettings.windowPosY;
	offset = (uint64_t*)0x14134D528;
	*(float*)offset = dbgMenuSettings.windowSizeX;
	offset = (uint64_t*)0x14134D52C;
	*(float*)offset = dbgMenuSettings.windowSizeY;
	offset = (uint64_t*)0x14134D530;
	*(float*)offset = dbgMenuSettings.windowScaleX;
	offset = (uint64_t*)0x14134D534;
	*(float*)offset = dbgMenuSettings.windowScaleY;
	offset = (uint64_t*)0x141D184F0;
	*(float*)offset = dbgMenuSettings.windowColorR;
	offset = (uint64_t*)0x141D184F4;
	*(float*)offset = dbgMenuSettings.windowColorG;
	offset = (uint64_t*)0x141D184F8;
	*(float*)offset = dbgMenuSettings.windowColorB;
	offset = (uint64_t*)0x141D184FC;
	*(float*)offset = dbgMenuSettings.windowColorA;
	offset = (uint64_t*)0x141D18500;
	*(float*)offset = dbgMenuSettings.activeWindowColorR;
	offset = (uint64_t*)0x141D18504;
	*(float*)offset = dbgMenuSettings.activeWindowColorG;
	offset = (uint64_t*)0x141D18508;
	*(float*)offset = dbgMenuSettings.activeWindowColorB;
	offset = (uint64_t*)0x141D1850C;
	*(float*)offset = dbgMenuSettings.activeWindowColorA;

	BYTE textHighlightColorR = 255 * dbgMenuSettings.textHighlightColorR;
	BYTE textHighlightColorG = 255 * dbgMenuSettings.textHighlightColorG;
	BYTE textHighlightColorB = 255 * dbgMenuSettings.textHighlightColorB;
	BYTE textHighlightColorA = 255 * dbgMenuSettings.textHighlightColorA;

	textHighlightColor = textHighlightColorB | (textHighlightColorG << 8) | (textHighlightColorR << 16) | (textHighlightColorA << 24);

	
}

DWORD ConvertColor(float input[4])
{
	DWORD output;

	BYTE color0 = 255 * input[0];
	BYTE color1 = 255 * input[1];
	BYTE color2 = 255 * input[2];
	BYTE color3 = 255 * input[3];

	output = color2 | (color1 << 8) | (color0 << 16) | (color3 << 24);

	return output;
}

void LoadCoreOptionSection()
{
	DWORD oldProtect;
	bool patchSystem = GetPrivateProfileInt(L"Core", L"IO.PatchSystem.Enabled", 0, L"./game.properties");

	if (patchSystem)
	{
		if (VirtualProtect((LPVOID)0x1400C4C80, 2, PAGE_EXECUTE_READWRITE, &oldProtect))
		{
			memcpy((void*)0x1400C4C80, patching_system, 2);
			VirtualProtect((LPVOID)0x1400C4C80, 2, oldProtect, &oldProtect);
		}
	}
}

void LoadDbgOutputConsoleOptionSection()
{
	_locale_t locale = _create_locale(LC_NUMERIC, "en-US");
	wchar_t buffer[32];

	GetPrivateProfileString(L"DbgOutputConsole", L"Def.WindowPos.X", L"800.0", buffer, 32, L"./game.properties");
	g_DbgConsolePosX = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgOutputConsole", L"Def.WindowPos.Y", L"100.0", buffer, 32, L"./game.properties");
	g_DbgConsolePosY = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgOutputConsole", L"Def.WindowSize.X", L"520.0", buffer, 32, L"./game.properties");
	g_DbgConsoleSizeX = _wtof_l(buffer, locale);
	GetPrivateProfileString(L"DbgOutputConsole", L"Def.WindowSize.Y", L"600.0", buffer, 32, L"./game.properties");
	g_DbgConsoleSizeY = _wtof_l(buffer, locale);
}

void LoadQLOCOptionSectionForBoot()
{
	DWORD oldProtect;
	BYTE mov_al_Patch[5] = { 0xB0, 0x00, 0x90, 0x90, 0x90 };
	BYTE mov_eax_Patch[5] = { 0xB8, 0x00, 0x00, 0x00, 0x00 };

	bool playerIgnoreOwnLight = GetPrivateProfileInt(L"QLOC", L"Render.PlayerIgnoreOwnLight", 1, L"./game.properties");
	bool disableRNG = GetPrivateProfileInt(L"QLOC", L"Debug.DisableRNG", 1, L"./game.properties");
	int recordOnStartup = GetPrivateProfileInt(L"QLOC", L"Debug.RecordOnStartup", -1, L"./game.properties");
	int playbackOnStartup = GetPrivateProfileInt(L"QLOC", L"Debug.PlaybackOnStartup", -1, L"./game.properties");
	bool clipCursor = GetPrivateProfileInt(L"QLOC", L"Debug.ClipCursor", 1, L"./game.properties");
	int useDevServer = GetPrivateProfileInt(L"QLOC", L"Debug.UseDevServer", 0, L"./game.properties");

	mov_al_Patch[1] = playerIgnoreOwnLight;

	VirtualProtect((LPVOID)0x140356350, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x140356350, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x140356350, 5, oldProtect, &oldProtect);

	mov_al_Patch[1] = disableRNG;

	VirtualProtect((LPVOID)0x1402C315A, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1402C315A, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x1402C315A, 5, oldProtect, &oldProtect);

	*(int*)(mov_eax_Patch + 1) = recordOnStartup;

	//this is only half... but who cares LUL
	VirtualProtect((LPVOID)0x14017663B, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14017663B, mov_eax_Patch, 5);
	VirtualProtect((LPVOID)0x14017663B, 5, oldProtect, &oldProtect);

	*(int*)(mov_eax_Patch + 1) = playbackOnStartup;

	VirtualProtect((LPVOID)0x140176642, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x140176642, mov_eax_Patch, 5);
	VirtualProtect((LPVOID)0x140176642, 5, oldProtect, &oldProtect);

	mov_al_Patch[1] = clipCursor;

	VirtualProtect((LPVOID)0x14017EF8B, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14017EF8B, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x14017EF8B, 5, oldProtect, &oldProtect);

	mov_al_Patch[1] = useDevServer;

	VirtualProtect((LPVOID)0x1407F6C04, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1407F6C04, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x1407F6C04, 5, oldProtect, &oldProtect);

	
}

void LoadHgManOptionSection()
{
	DWORD oldProtect;
	BYTE mov_al_Patch[5] = { 0xB0, 0x00, 0x90, 0x90, 0x90 };

	bool vsyncEnabled = GetPrivateProfileInt(L"HgMan", L"VSyncEnabled", 1, L"./game.properties");

	mov_al_Patch[1] = vsyncEnabled;
	VirtualProtect((LPVOID)0x14015EAEC, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14015EAEC, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x14015EAEC, 5, oldProtect, &oldProtect);
}

void LoadMoveMapMenuOptionSection()
{
	DWORD oldProtect;
	BYTE mov_eax_Patch[5] = { 0xB8, 0x00, 0x00, 0x00, 0x00 };

	int selectIdx = GetPrivateProfileInt(L"MoveMapMenu", L"Def.SelectIdx", 0, L"./game.properties");

	*(int*)(mov_eax_Patch + 1) = selectIdx;

	VirtualProtect((LPVOID)0x14024B9F2, 0x30, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14024B9F2, mov_eax_Patch, 5);
	memcpy((void*)0x14024BA18, mov_eax_Patch, 5);
	VirtualProtect((LPVOID)0x14024B9F2, 0x30, oldProtect, &oldProtect);

}

void LoadBootMenuOptionSection()
{
	DWORD oldProtect;
	BYTE mov_eax_Patch[5] = { 0xB8, 0x00, 0x00, 0x00, 0x00 };

	int selectIdx = GetPrivateProfileInt(L"BootMenu", L"Def.SelectIdx", 0, L"./game.properties");

	*(int*)(mov_eax_Patch + 1) = selectIdx;

	VirtualProtect((LPVOID)0x14025DB92, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14025DB92, mov_eax_Patch, 5);
	VirtualProtect((LPVOID)0x14025DB92, 5, oldProtect, &oldProtect);
}

void LoadAiOptionSection()
{
	DWORD oldProtect;
	BYTE mov_al_Patch[5] = { 0xB0, 0x00, 0x90, 0x90, 0x90 };

	bool isDbgDrawPathFindingResult = GetPrivateProfileInt(L"AI", L"IsDbgDrawPathFindingResult", 0, L"./game.properties");
	bool isDbgDrawCurrentTarget = GetPrivateProfileInt(L"AI", L"Targeting.IsDbgDrawCurrentTarget", 0, L"./game.properties");
	bool isDbgDrawPlayerAroundNvm = GetPrivateProfileInt(L"AI", L"Navigation.IsDbgDrawPlayerAroundNvm", 0, L"./game.properties");
	bool isDbgDrawMap_forNvm = GetPrivateProfileInt(L"AI", L"Navigation.IsDbgDrawMap_forNvm", 1, L"./game.properties");

	mov_al_Patch[1] = isDbgDrawPathFindingResult;

	VirtualProtect((LPVOID)0x1405E760A, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1405E760A, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x1405E760A, 5, oldProtect, &oldProtect);

	mov_al_Patch[1] = isDbgDrawCurrentTarget;

	VirtualProtect((LPVOID)0x140619CCE, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x140619CCE, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x140619CCE, 5, oldProtect, &oldProtect);

	mov_al_Patch[1] = isDbgDrawPlayerAroundNvm;

	VirtualProtect((LPVOID)0x1405F0E94, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1405F0E94, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x1405F0E94, 5, oldProtect, &oldProtect);

	mov_al_Patch[1] = isDbgDrawMap_forNvm;

	VirtualProtect((LPVOID)0x1405F0E9F, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1405F0E9F, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x1405F0E9F, 5, oldProtect, &oldProtect);
}

void LoadGameRuleOptionSection()
{
	DWORD oldProtect;
	BYTE mov_al_Patch[5] = { 0xB0, 0x00, 0x90, 0x90, 0x90 };

	bool isDbgMaxBaseEquipWeight = GetPrivateProfileInt(L"GameRule", L"IsDbgMaxBaseEquipWeight", 0, L"./game.properties");

	mov_al_Patch[1] = isDbgMaxBaseEquipWeight;

	VirtualProtect((LPVOID)0x1402DFEB9, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1402DFEB9, mov_al_Patch, 5);
	VirtualProtect((LPVOID)0x1402DFEB9, 5, oldProtect, &oldProtect);
}

void LoadGameDataOptionSection()
{
	DWORD oldProtect;
	BYTE mov_al_Patch[5] = { 0xB0, 0x00, 0x90, 0x90, 0x90 };

	bool playerNoDead = GetPrivateProfileInt(L"GameData", L"PlayerNoDead", 0, L"./game.properties");
	bool playerExterminate = GetPrivateProfileInt(L"GameData", L"PlayerExterminate", 0, L"./game.properties");
	bool playerHide = GetPrivateProfileInt(L"GameData", L"PlayerHide", 0, L"./game.properties");
	bool playerSilence= GetPrivateProfileInt(L"GameData", L"PlayerSilence", 0, L"./game.properties");
	bool allNoDead = GetPrivateProfileInt(L"GameData", L"AllNoDead", 0, L"./game.properties");
	bool allNoDamage = GetPrivateProfileInt(L"GameData", L"AllNoDamage", 0, L"./game.properties");
	bool allNoHit = GetPrivateProfileInt(L"GameData", L"AllNoHit", 0, L"./game.properties");
	bool allNoAttack = GetPrivateProfileInt(L"GameData", L"AllNoAttack", 0, L"./game.properties");
	bool allNoMove = GetPrivateProfileInt(L"GameData", L"AllNoMove", 0, L"./game.properties");
	bool allNoUpdateAi = GetPrivateProfileInt(L"GameData", L"AllNoUpdateAi", 0, L"./game.properties");
	bool allNoStaminaConsume = GetPrivateProfileInt(L"GameData", L"AllNoStaminaConsume", 0, L"./game.properties");
	bool allNoMpConsume = GetPrivateProfileInt(L"GameData", L"AllNoMpConsume", 0, L"./game.properties");
	bool allNoArrowConsume = GetPrivateProfileInt(L"GameData", L"AllNoArrowConsume", 0, L"./game.properties");
	bool allNoMagicQtyConsume = GetPrivateProfileInt(L"GameData", L"AllNoMagicQtyConsume", 0, L"./game.properties");
	bool allDrawHit = GetPrivateProfileInt(L"GameData", L"AllDrawHit", 0, L"./game.properties");
	bool npcDispLocalCtrl = GetPrivateProfileInt(L"GameData", L"NpcDispLocalCtrl", 0, L"./game.properties");
	bool debugDashSwitch = GetPrivateProfileInt(L"GameData", L"DebugDashSwitch", 1, L"./game.properties");
	bool enablePlayerReload = GetPrivateProfileInt(L"GameData", L"EnablePlayerReload", 0, L"./game.properties");

	*(BYTE*)0x141D151C9 = playerNoDead;
	*(BYTE*)0x141D151CA = playerExterminate;
	*(BYTE*)0x141D151CB = allNoStaminaConsume;
	*(BYTE*)0x141D151CC = allNoMpConsume;
	*(BYTE*)0x141D151CD = allNoArrowConsume;
	*(BYTE*)0x141D151CE = allNoMagicQtyConsume;
	*(BYTE*)0x141D151CF = playerHide;
	*(BYTE*)0x141D151D0 = playerSilence;
	*(BYTE*)0x141D151D1 = allNoDead;
	*(BYTE*)0x141D151D2 = allNoDamage;
	*(BYTE*)0x141D151D3 = allNoHit;
	*(BYTE*)0x141D151D4 = allNoAttack;
	*(BYTE*)0x141D151D5 = allNoMove;
	*(BYTE*)0x141D151D6 = allNoUpdateAi;
	*(BYTE*)0x141D151DA = debugDashSwitch;
	*(BYTE*)0x141D151DB = enablePlayerReload;

	worldChrManDbgSettings.allDrawHit = allDrawHit;
	worldChrManDbgSettings.npcDispLocalCtrl = npcDispLocalCtrl;
}

void LoadGameOptionSection()
{
	DWORD oldProtect;

	unsigned int initEquipParamId = GetPrivateProfileInt(L"Game", L"InitEquipParamId", 9000, L"./game.properties");
	uint32_t deadRagdollKickType = GetPrivateProfileInt(L"Game", L"DeadRagdollKickType", 2, L"./game.properties");
	bool isUseChrFollowCam = GetPrivateProfileInt(L"Game", L"IsUseChrFollowCam", 1, L"./game.properties");
	bool rotLR = GetPrivateProfileInt(L"Game", L"Option.Control.RotLR", 1, L"./game.properties");
	bool rotUD = GetPrivateProfileInt(L"Game", L"Option.Control.RotUD", 1, L"./game.properties");
	BYTE rotSpeed = GetPrivateProfileInt(L"Game", L"Option.Control.RotSpeed", 5, L"./game.properties");
	BYTE rumble = GetPrivateProfileInt(L"Game", L"Option.Control.Rumble", 10, L"./game.properties");
	bool autoLockOn = GetPrivateProfileInt(L"Game", L"Option.Control.AutoLockOn", 1, L"./game.properties");
	bool autoWallRecover = GetPrivateProfileInt(L"Game", L"Option.Control.AutoWallRecovery", 1, L"./game.properties");
	BYTE blood = GetPrivateProfileInt(L"Game", L"Option.Disp.Blood", 1, L"./game.properties");
	BYTE subtitle = GetPrivateProfileInt(L"Game", L"Option.Disp.Subtitle", 1, L"./game.properties");
	BYTE brightness = GetPrivateProfileInt(L"Game", L"Option.Disp.Brightness", 5, L"./game.properties");
	BYTE soundType = GetPrivateProfileInt(L"Game", L"Option.Sound.SoundType", 0, L"./game.properties");
	BYTE voiceVol = GetPrivateProfileInt(L"Game", L"Option.Sound.VoiceVol", 7, L"./game.properties");
	BYTE seVol = GetPrivateProfileInt(L"Game", L"Option.Sound.SeVol", 7, L"./game.properties");
	BYTE musicVol = GetPrivateProfileInt(L"Game", L"Option.Sound.MusicVol", 7, L"./game.properties");
	BYTE uiScale = GetPrivateProfileInt(L"Game", L"Option.UI.Scale", 100, L"./game.properties");

	bool isUseLuaConsole = GetPrivateProfileInt(L"Game", L"IsUseDbgConsole", 0, L"./game.properties");

	bool trueDead = GetPrivateProfileInt(L"Game", L"Event.TrueDead", 1, L"./game.properties");

	unsigned long long* gameDataMan = (unsigned long long*)*(unsigned long long*)0x141D278F0;
	BYTE* sthPtr = (BYTE*)*(uint64_t*)0x141D19958;

	BYTE* options = (BYTE*)*(gameDataMan + 0xB);

	*(options + 0x8) = rotSpeed;
	*(options + 0x9) = rumble;
	*(options + 0xA) = brightness;
	*(options + 0xB) = soundType;
	*(options + 0xC) = musicVol;
	*(options + 0xD) = seVol;
	*(options + 0xE) = voiceVol;
	*(options + 0xF) = blood;
	*(options + 0x10) = subtitle;
	*(options + 0x12) = uiScale;
	*(options + 0x13) = rotLR;
	*(options + 0x14) = rotUD;
	*(options + 0x15) = autoLockOn;
	*(options + 0x16) = autoWallRecover;
	*(options + 0x48) = rotSpeed;

	*(sthPtr + 0x26) = trueDead;

	VirtualProtect((LPVOID)0x14075255E, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14075255E, &initEquipParamId, 4);
	VirtualProtect((LPVOID)0x14075255E, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x14018BAAB, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14018BAAB, &deadRagdollKickType, 4);
	VirtualProtect((LPVOID)0x14018BAAB, 4, oldProtect, &oldProtect);

	BYTE isUseChrFollowCamPatch[5] = { 0xB0, 0x00, 0x90, 0x90, 0x90 };
	isUseChrFollowCamPatch[1] = isUseChrFollowCam;

	VirtualProtect((LPVOID)0x1402350A0, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1402350A0, isUseChrFollowCamPatch, 5);
	VirtualProtect((LPVOID)0x1402350A0, 5, oldProtect, &oldProtect);

	g_isOpenConsole = isUseLuaConsole;
}

VOID LoadGameProperties()
{
	HANDLE ini;
	if ((ini = CreateFile(L"game.properties", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
	{
		CloseHandle(ini);

		LoadGameOptionSection();
		LoadDbgOutputConsoleOptionSection();
		LoadGameDataOptionSection();
		LoadGameRuleOptionSection();
		LoadAiOptionSection();
		LoadDamageManOptionSelection();
		//LoadDbgMenuSection();
		
	}
}

void LoadBootSettings()
{
	HANDLE ini;
	if ((ini = CreateFile(L"game.properties", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
	{
		CloseHandle(ini);

		LoadHgManOptionSection();
		LoadQLOCOptionSectionForBoot();
		LoadCoreOptionSection();
		LoadDbgMenuSection();
		LoadBootMenuOptionSection();
		LoadMoveMapMenuOptionSection();
	}
}

int ApplyPatches()
{
	DWORD oldProtect;
	BYTE patch = 0x60;
	uint64_t offset = 0;

	int hookLength = 0;

	if (!VirtualProtect((LPVOID)0x14015E33B, 7, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14015E33B, backgroundPatch, 7);
	VirtualProtect((LPVOID)0x14015E33B, 7, oldProtect, &oldProtect);

	long long  hookAddress = 0x1408E4C43;
	if (!VirtualProtect((LPVOID)hookAddress, 30, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)hookAddress, initDbgMenuPatch, 30);
	VirtualProtect((LPVOID)hookAddress, 30, oldProtect, &oldProtect);

	hookAddress = 0x140152A38;
	if (!VirtualProtect((LPVOID)hookAddress, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)hookAddress, initDbgMenuPatchJump, 5);
	VirtualProtect((LPVOID)hookAddress, 5, oldProtect, &oldProtect);

	//patch in new dbgMenuGetLabelNode
	hookAddress = 0x1408E4C2F;
	if (!VirtualProtect((LPVOID)hookAddress, 20, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)hookAddress, getDbgMenuLabelNodeFunc, 20);
	VirtualProtect((LPVOID)hookAddress, 20, oldProtect, &oldProtect);

	for (int i = 0; i < 26; i++)
	{
		uint64_t offset = getDbgMenuLabelNodeFuncCalls[i] + 1;
		if (!VirtualProtect((LPVOID)offset, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
			return false;
		//memcpy((void*)offset, &fDrawDebugMenu, 8);
		int diff = hookAddress - offset - 4;
		*(int*)offset = diff;
		VirtualProtect((LPVOID)offset, 4, oldProtect, &oldProtect);
	}

	hookAddress = 0x14015E594;
	if (!VirtualProtect((LPVOID)hookAddress, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)hookAddress, &ezDrawDbgMenuBufferSize, 4);
	VirtualProtect((LPVOID)hookAddress, 4, oldProtect, &oldProtect);

	hookAddress = 0x1401B67F3;
	hookLength = 7;
	bLoadGamePropertiesOrSth = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tLoadGamePropertiesOrSth, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//if (!VirtualProtect((LPVOID)0x14015CF6A, 1, PAGE_EXECUTE_READWRITE, &oldProtect))
	//	return false;
	//memcpy((void*)0x14015CF6A, &patch, 1);
	//VirtualProtect((LPVOID)0x14015CF6A, 1, oldProtect, &oldProtect);

	//hookLength = 6;
	//hookAddress = 0x140214924;
	//bGetCameraObj = hookAddress + hookLength;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)fGetCameraObj, 0);
	//MH_EnableHook((LPVOID)hookAddress);

	///*hookLength = 6;
	//hookAddress = 0x14021E734;
	//bGetCameraObjAlt = hookAddress + hookLength;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)fGetCameraObjAlt, 0);
	//MH_EnableHook((LPVOID)hookAddress);*/

	//hookLength = 7;
	//hookAddress = 0x1401E05B3;
	//bSetCameraObj = hookAddress + hookLength;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)fSetCameraObj, 0);
	//MH_EnableHook((LPVOID)hookAddress);

	if (!VirtualProtect((LPVOID)0x1402773F7, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1402773F7, boot_patch, 4);
	VirtualProtect((LPVOID)0x1402773F7, 4, oldProtect, &oldProtect);

	patch = 3;

	if (!VirtualProtect((LPVOID)0x1401E8EBF, 1, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1401E8EBF, &patch, 1);
	VirtualProtect((LPVOID)0x1401E8EBF, 1, oldProtect, &oldProtect);

	//this doesn't do anything, too late
	//increase lua memory
	unsigned int patchy = 0x9C4000;

	if (!VirtualProtect((LPVOID)0x140168312, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x140168312, &patchy, 4);
	VirtualProtect((LPVOID)0x140168312, 4, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x140168339, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x140168339, &patchy, 4);
	VirtualProtect((LPVOID)0x140168339, 4, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x14016837B, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14016837B, &patchy, 4);
	VirtualProtect((LPVOID)0x14016837B, 4, oldProtect, &oldProtect);

	BYTE fmodPatch[7] = { 0xB9, 0xFF, 0, 0, 0, 0xEB, 0x36 };

	//FMOD shit
	/*if (!VirtualProtect((LPVOID)0x1410117AE, 7, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1410117AE, fmodPatch, 7);
	VirtualProtect((LPVOID)0x1410117AE, 7, oldProtect, &oldProtect);*/

	//restore original debug memory
	//unsigned int debugMem = 0x200000;

	//if (!VirtualProtect((LPVOID)0x140168891, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
	//	return false;
	//memcpy((void*)0x140168891, &debugMem, 4);
	//VirtualProtect((LPVOID)0x140168891, 4, oldProtect, &oldProtect);

	//if (!VirtualProtect((LPVOID)0x1401688B8, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
	//	return false;
	//memcpy((void*)0x1401688B8, &debugMem, 4);
	//VirtualProtect((LPVOID)0x1401688B8, 4, oldProtect, &oldProtect);

	//if (!VirtualProtect((LPVOID)0x1401688FE, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
	//	return false;
	//memcpy((void*)0x1401688FE, &debugMem, 4);
	//VirtualProtect((LPVOID)0x1401688FE, 4, oldProtect, &oldProtect);

	//fix navimesh drawing
	/*if (!VirtualProtect((LPVOID)0x1405F0E8E, 6, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1405F0E8E, navi_patch, 6);
	VirtualProtect((LPVOID)0x1405F0E8E, 6, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x1405F143C, 9, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1405F143C, navi_patch2, 9);
	VirtualProtect((LPVOID)0x1405F143C, 9, oldProtect, &oldProtect);
	
	if (!VirtualProtect((LPVOID)0x1405F14C3, 8, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1405F14C3, navi_patch3, 8);
	VirtualProtect((LPVOID)0x1405F14C3, 8, oldProtect, &oldProtect);*/

	/*if (!VirtualProtect((LPVOID)0x1405F14C3, 8, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1405F14C3, navi_patch3, 8);
	VirtualProtect((LPVOID)0x1405F14C3, 8, oldProtect, &oldProtect);*/
	
	//load game.properties
	hookLength = 7;
	hookAddress = 0x14025E10B;
	bLoadGameProperties = hookAddress + hookLength;
	//fLoadGameProperties = (DWORD64)(LPVOID)LoadGameProperties;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tLoadGameProperties, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//under construction
	hookLength = 6;
	hookAddress = 0x140522043;
	bAddUnderConstructionParamMan = hookAddress + hookLength;
	//fLoadGameProperties = (DWORD64)(LPVOID)LoadGameProperties;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fAddUnderConstructionParamMan, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 10;
	hookAddress = 0x1407C3576;
	bAddUnderConstructionEmevdMan = hookAddress + hookLength;
	//fLoadGameProperties = (DWORD64)(LPVOID)LoadGameProperties;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fAddUnderConstructionEmevdMan, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//1432AEAB8 init
	hookAddress = 0x1432AEAB8;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)loadEnemyMsbName, 0);
	MH_EnableHook((LPVOID)hookAddress);
	
	hookLength = 6;
	hookAddress = 0x140175075;
	bWritePlayerName = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)writePlayerName, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//1422847E1 free
	hookAddress = 0x1422847E1;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)freeEnemyMsbName, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//patch dbg menu control/drawing members

	for (int i = 0; i < 106; i++)
	{
		offset = dbgMenuControlVtableOffsets[i];
		if (!VirtualProtect((LPVOID)offset, 16, PAGE_EXECUTE_READWRITE, &oldProtect))
			return false;
		//memcpy((void*)offset, &fDrawDebugMenu, 8);
		*(uint64_t*)offset = (uint64_t)fControlDebugMenu;
		*(uint64_t*)(offset+8) = (uint64_t)fDrawDebugMenu;
		VirtualProtect((LPVOID)offset, 16, oldProtect, &oldProtect);
	}

	//draw dbg menu
	hookLength = 10;
	hookAddress = 0x14015BE2A;
	bDrawDebugMenuGOGOGO = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tDrawDebugMenuGOGOGO, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//fix strings
	if (!VirtualProtect((LPVOID)0x14131D2A0, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14131D2A0, &fullCircleUTF16, 4);
	VirtualProtect((LPVOID)0x14131D2A0, 4, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x14131C668, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14131C668, &emptyCircleUTF16, 4);
	VirtualProtect((LPVOID)0x14131C668, 4, oldProtect, &oldProtect);

	//patch gesture menu button combo
	BYTE je = 0x74;

	if (!VirtualProtect((LPVOID)0x1401A3435, 1, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1401A3435, &je, 1);
	VirtualProtect((LPVOID)0x1401A3435, 1, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x1401A3447, 1, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1401A3447, &je, 1);
	VirtualProtect((LPVOID)0x1401A3447, 1, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x1401A3449, 32, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1401A3449, gestureMenuPatch, 32);
	VirtualProtect((LPVOID)0x1401A3449, 32, oldProtect, &oldProtect);

	LoadBootSettings();

	//restore debug dash
	hookLength = 5;
	hookAddress = 0x140370122;
	bCheckDebugDash = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tCheckDebugDash, 0);
	MH_EnableHook((LPVOID)hookAddress);

	BYTE enable = 1;

	if (!VirtualProtect((LPVOID)0x141D151DA, 1, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x141D151DA, &enable, 1);
	VirtualProtect((LPVOID)0x141D151DA, 1, oldProtect, &oldProtect);

	offset = 0x141AC56D8;

	if (!VirtualProtect((LPVOID)offset, 8, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	*(uint64_t*)offset = (uint64_t)fDbgDispLoading;
	VirtualProtect((LPVOID)offset, 8, oldProtect, &oldProtect);

	hookLength = 8;
	hookAddress = 0x1402CD384;
	bEzDrawAddDrawPlans1 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans1, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 8;
	hookAddress = 0x1402CD626;
	bEzDrawAddDrawPlans2 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans2, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 8;
	hookAddress = 0x1402CD851;
	bEzDrawAddDrawPlans3 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans3, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 8;
	hookAddress = 0x1402CDAE7;
	bEzDrawAddDrawPlans4 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans4, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 8;
	hookAddress = 0x1402CDD92;
	bEzDrawAddDrawPlans5 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans5, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x1402CF099;
	bEzDrawAddDrawPlans6 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans6, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 7;
	hookAddress = 0x14027993A;
	bApplySettingsDamageMan = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fApplySettingsDamageMan, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14036E3D6;
	bApplySettingsWorldChrManDbg = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fApplySettingsWorldChrManDbg, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//meow patch for m99 ffxbnd
	if (!VirtualProtect((LPVOID)0x1404FA954, 6, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1404FA954, dbg_patch, 6);
	VirtualProtect((LPVOID)0x1404FA954, 6, oldProtect, &oldProtect);

	//LUL
	hookLength = 7;
	hookAddress = 0x14028D4F1;
	bRemoAddTest = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fRemoAddTest, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//open console
	hookLength = 7;
	hookAddress = 0x140627AFE;
	bOpenLogConsole = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fOpenLogConsole, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//FreeCam
	hookLength = 7;
	hookAddress = 0x14024DF91;
	bFreeCam = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fFreeCam, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//leave commented out
	/*if (!VirtualProtect((LPVOID)0x14024EB29, 6, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14024EB29, freeCamPatch, 6);
	VirtualProtect((LPVOID)0x14024EB29, 6, oldProtect, &oldProtect);*/

	//more freecam
	/*hookLength = 5;
	hookAddress = 0x1400C5FD4;
	bGetFreeCamMode1 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tGetFreeCamMode1, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14024EB21;
	bGetFreeCamMode2 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tGetFreeCamMode2, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14024EFA2;
	bGetFreeCamMode3 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tGetFreeCamMode3, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14024F1C7;
	bGetFreeCamMode4 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tGetFreeCamMode4, 0);
	MH_EnableHook((LPVOID)hookAddress);*/

	//L3 + R3 Exit
	hookLength = 5;
	hookAddress = 0x14024B07B;
	bExitButtonComboCheck1 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tExitButtonComboCheck1, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14025622C;
	bExitButtonComboCheck2 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tExitButtonComboCheck2, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14027AF42;
	bExitButtonComboCheck3 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tExitButtonComboCheck3, 0);
	MH_EnableHook((LPVOID)hookAddress);
	
	//slow down DbgCamera movement (0.25 multiplier instead of 0.5)
	if (!VirtualProtect((LPVOID)0x14019C1F2, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14019C1F2, dbgCamZSpeedPatch, 4);
	VirtualProtect((LPVOID)0x14019C1F2, 4, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x14019C3EC, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14019C3EC, dbgCamYSpeedPatch, 4);
	VirtualProtect((LPVOID)0x14019C3EC, 4, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x14019C2E2, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14019C2E2, dbgCamXSpeedPatch, 4);
	VirtualProtect((LPVOID)0x14019C2E2, 4, oldProtect, &oldProtect);

	return 1;
}

void PatchGame()
{
	puts("Starting patching process...");

	DWORD oldProtect;
	uint64_t offset = 0;
	long long hookAddress = 0;
	int hookLength = 0;
	int numPatches = 2 + gamePatches.size();
	/*VirtualProtect((LPVOID)0x1420B52F0, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(uint64_t*)0x1420B52F0 = 0x140152AF0;
	VirtualProtect((LPVOID)0x1420B52F0, 8, PAGE_EXECUTE_READWRITE, &oldProtect);*/

	//load paramdefbnd
	//int hookLength = 7;
	//long long hookAddress = 0x1402611D2;
	//bLoadParamdefbnd = hookAddress + hookLength;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)tLoadParamdefbnd, 0);
	//MH_EnableHook((LPVOID)hookAddress);

	//exception filter stuff. useless? not useless
	/*VirtualProtect((LPVOID)0x1420B52F0, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(uint64_t*)0x1420B52F0 = 0x140152AF0;
	VirtualProtect((LPVOID)0x1420B52F0, 8, PAGE_EXECUTE_READWRITE, &oldProtect);

	SetUnhandledExceptionFilter(UHFilter);*/

	for (int i = 0; i < 26; i++)
	{
		//AddHOOKPatch(getDbgMenuLabelNodeFuncCalls[i], 5, getDbgMenuLabelNodeFuncCallsLastByte[i], &fGetDebugMenuLabelNode, NULL, 0, true);

		//while (*(BYTE*)getDbgMenuLabelNodeFuncCalls[i] != 0xE8);
		MH_CreateHook((LPVOID)getDbgMenuLabelNodeFuncCalls[i], (LPVOID)fGetDebugMenuLabelNode, 0);
		MH_EnableHook((LPVOID)getDbgMenuLabelNodeFuncCalls[i]);
		*(BYTE*)getDbgMenuLabelNodeFuncCalls[i] = 0xE8;

		//uint64_t offset = getDbgMenuLabelNodeFuncCalls[i] + 1;
		//VirtualProtect((LPVOID)offset, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
		////memcpy((void*)offset, &fDrawDebugMenu, 8);
		//int diff = (uint64_t)haha - offset - 4;
		//*(int*)offset = diff;
		//VirtualProtect((LPVOID)offset, 4, oldProtect, &oldProtect);

	}

	printf("(1/%i)", numPatches);

	for (int i = 0; i < 106; i++)
	{
		offset = dbgMenuControlVtableOffsets[i];
		VirtualProtect((LPVOID)offset, 16, PAGE_EXECUTE_READWRITE, &oldProtect);
		//memcpy((void*)offset, &fDrawDebugMenu, 8);
		*(uint64_t*)offset = (uint64_t)fControlDebugMenu;
		*(uint64_t*)(offset + 8) = (uint64_t)fDrawDebugMenu;
		VirtualProtect((LPVOID)offset, 16, oldProtect, &oldProtect);
	}

	printf("\r(2/%i)", numPatches);
	
	for (int i = 0; i < gamePatches.size(); i++)
	{
		ProcessPatch(&gamePatches[i]);

		printf("\r(%i/%i)", i + 3, numPatches);
	}

	puts("");
	puts("Patching done");

	return;

	VirtualProtect((LPVOID)0x14015E33B, 7, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14015E33B, backgroundPatch, 7);
	VirtualProtect((LPVOID)0x14015E33B, 7, oldProtect, &oldProtect);

	MH_CreateHook((LPVOID)0x140152A38, (LPVOID)fInitRootDbgMenuLabelNode, 0);
	MH_EnableHook((LPVOID)0x140152A38);
	
	hookAddress = 0x14015E594;
	VirtualProtect((LPVOID)hookAddress, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)hookAddress, &ezDrawDbgMenuBufferSize, 4);
	VirtualProtect((LPVOID)hookAddress, 4, oldProtect, &oldProtect);

	hookAddress = 0x1401B67F3;
	hookLength = 7;
	bLoadGamePropertiesOrSth = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tLoadGamePropertiesOrSth, 0);
	MH_EnableHook((LPVOID)hookAddress);
	
	//esd output log
	MH_CreateHook((LPVOID)0x1403913ED, (LPVOID)tEsdDbgLogOutput, 0);
	MH_EnableHook((LPVOID)0x1403913ED);

	void* ptr = &PrintText;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)PrintText, 0);
	//MH_EnableHook((LPVOID)hookAddress);
	VirtualProtect((LPVOID)0x141ACCC18, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x141ACCC18, &ptr, 8);
	VirtualProtect((LPVOID)0x141ACCC18, 8, oldProtect, &oldProtect);

	hookAddress = 0x14047BB44;
	hookLength = 5;
	bLoadDbgMenuTextHighlightColor = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tLoadDbgMenuTextHighlightColor, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//if (!VirtualProtect((LPVOID)0x14015CF6A, 1, PAGE_EXECUTE_READWRITE, &oldProtect))
	//	return false;
	//memcpy((void*)0x14015CF6A, &patch, 1);
	//VirtualProtect((LPVOID)0x14015CF6A, 1, oldProtect, &oldProtect);

	//hookLength = 6;
	//hookAddress = 0x140214924;
	//bGetCameraObj = hookAddress + hookLength;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)fGetCameraObj, 0);
	//MH_EnableHook((LPVOID)hookAddress);

	///*hookLength = 6;
	//hookAddress = 0x14021E734;
	//bGetCameraObjAlt = hookAddress + hookLength;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)fGetCameraObjAlt, 0);
	//MH_EnableHook((LPVOID)hookAddress);*/

	//hookLength = 7;
	//hookAddress = 0x1401E05B3;
	//bSetCameraObj = hookAddress + hookLength;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)fSetCameraObj, 0);
	//MH_EnableHook((LPVOID)hookAddress);

	VirtualProtect((LPVOID)0x1402773F7, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1402773F7, boot_patch, 4);
	VirtualProtect((LPVOID)0x1402773F7, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x1401E8EBF, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1401E8EBF, &blendstate_patch, 1);
	VirtualProtect((LPVOID)0x1401E8EBF, 1, oldProtect, &oldProtect);

	
	//works up to here
	BYTE fmodPatch[7] = { 0xB9, 0xFF, 0, 0, 0, 0xEB, 0x36 };

	//FMOD shit
	/*if (!VirtualProtect((LPVOID)0x1410117AE, 7, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1410117AE, fmodPatch, 7);
	VirtualProtect((LPVOID)0x1410117AE, 7, oldProtect, &oldProtect);*/

	//restore original debug memory
	//unsigned int debugMem = 0x200000;

	//if (!VirtualProtect((LPVOID)0x140168891, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
	//	return false;
	//memcpy((void*)0x140168891, &debugMem, 4);
	//VirtualProtect((LPVOID)0x140168891, 4, oldProtect, &oldProtect);

	//if (!VirtualProtect((LPVOID)0x1401688B8, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
	//	return false;
	//memcpy((void*)0x1401688B8, &debugMem, 4);
	//VirtualProtect((LPVOID)0x1401688B8, 4, oldProtect, &oldProtect);

	//if (!VirtualProtect((LPVOID)0x1401688FE, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
	//	return false;
	//memcpy((void*)0x1401688FE, &debugMem, 4);
	//VirtualProtect((LPVOID)0x1401688FE, 4, oldProtect, &oldProtect);

	//fix navimesh drawing
	/*if (!VirtualProtect((LPVOID)0x1405F0E8E, 6, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1405F0E8E, navi_patch, 6);
	VirtualProtect((LPVOID)0x1405F0E8E, 6, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x1405F143C, 9, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1405F143C, navi_patch2, 9);
	VirtualProtect((LPVOID)0x1405F143C, 9, oldProtect, &oldProtect);

	if (!VirtualProtect((LPVOID)0x1405F14C3, 8, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1405F14C3, navi_patch3, 8);
	VirtualProtect((LPVOID)0x1405F14C3, 8, oldProtect, &oldProtect);*/

	/*if (!VirtualProtect((LPVOID)0x1405F14C3, 8, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x1405F14C3, navi_patch3, 8);
	VirtualProtect((LPVOID)0x1405F14C3, 8, oldProtect, &oldProtect);*/

	//load game.properties
	//hookLength = 7;
	//hookAddress = 0x14025E10B;
	//bLoadGameProperties = hookAddress + hookLength;
	////fLoadGameProperties = (DWORD64)(LPVOID)LoadGameProperties;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)tLoadGameProperties, 0);
	//MH_EnableHook((LPVOID)hookAddress);

	//load game.properties
	//hookLength = 7;
	//hookAddress = 0x14025E10B;
	//bLoadGameProperties = hookAddress + hookLength;
	////fLoadGameProperties = (DWORD64)(LPVOID)LoadGameProperties;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)tLoadGameProperties, 0);
	//MH_EnableHook((LPVOID)hookAddress);

	//under construction
	hookLength = 6;
	hookAddress = 0x140522043;
	bAddUnderConstructionParamMan = hookAddress + hookLength;
	//fLoadGameProperties = (DWORD64)(LPVOID)LoadGameProperties;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fAddUnderConstructionParamMan, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 10;
	hookAddress = 0x1407C3576;
	bAddUnderConstructionEmevdMan = hookAddress + hookLength;
	//fLoadGameProperties = (DWORD64)(LPVOID)LoadGameProperties;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fAddUnderConstructionEmevdMan, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//1432AEAB8 init
	hookAddress = 0x1432AEAB8;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)loadEnemyMsbName, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 6;
	hookAddress = 0x140175075;
	bWritePlayerName = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)writePlayerName, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//1422847E1 free
	hookAddress = 0x1422847E1;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)freeEnemyMsbName, 0);
	MH_EnableHook((LPVOID)hookAddress);
	
	//draw dbg menu
	hookLength = 10;
	hookAddress = 0x14015BE2A;
	bDrawDebugMenuGOGOGO = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tDrawDebugMenuGOGOGO, 0);
	MH_EnableHook((LPVOID)hookAddress);
	
	//fix strings
	VirtualProtect((LPVOID)0x14131D2A0, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14131D2A0, fullCircleUTF16, 4);
	VirtualProtect((LPVOID)0x14131D2A0, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x14131C668, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14131C668, emptyCircleUTF16, 4);
	VirtualProtect((LPVOID)0x14131C668, 4, oldProtect, &oldProtect);

	//patch gesture menu button combo
	/*VirtualProtect((LPVOID)0x1401A3435, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1401A3435, &gesturecombo_patch, 1);
	VirtualProtect((LPVOID)0x1401A3435, 1, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x1401A3447, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1401A3447, &gesturecombo_patch, 1);
	VirtualProtect((LPVOID)0x1401A3447, 1, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x1401A3449, 32, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1401A3449, gestureMenuPatch, 32);
	VirtualProtect((LPVOID)0x1401A3449, 32, oldProtect, &oldProtect);*/

	//LoadBootSettings();

	//restore debug dash
	hookLength = 5;
	hookAddress = 0x140370122;
	bCheckDebugDash = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tCheckDebugDash, 0);
	MH_EnableHook((LPVOID)hookAddress);

	VirtualProtect((LPVOID)0x141D151DA, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x141D151DA, &debugdashenable_patch, 1);
	VirtualProtect((LPVOID)0x141D151DA, 1, oldProtect, &oldProtect);

	offset = 0x141AC56D8;

	VirtualProtect((LPVOID)offset, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(uint64_t*)offset = (uint64_t)fDbgDispLoading;
	VirtualProtect((LPVOID)offset, 8, oldProtect, &oldProtect);

	hookLength = 8;
	hookAddress = 0x1402CD384;
	bEzDrawAddDrawPlans1 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans1, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 8;
	hookAddress = 0x1402CD626;
	bEzDrawAddDrawPlans2 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans2, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 8;
	hookAddress = 0x1402CD851;
	bEzDrawAddDrawPlans3 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans3, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 8;
	hookAddress = 0x1402CDAE7;
	bEzDrawAddDrawPlans4 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans4, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 8;
	hookAddress = 0x1402CDD92;
	bEzDrawAddDrawPlans5 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans5, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x1402CF099;
	bEzDrawAddDrawPlans6 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tEzDrawAddDrawPlans6, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 7;
	hookAddress = 0x14027993A;
	bApplySettingsDamageMan = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fApplySettingsDamageMan, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14036E3D6;
	bApplySettingsWorldChrManDbg = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fApplySettingsWorldChrManDbg, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//meow patch for m99 ffxbnd
	VirtualProtect((LPVOID)0x1404FA954, 6, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1404FA954, dbg_patch, 6);
	VirtualProtect((LPVOID)0x1404FA954, 6, oldProtect, &oldProtect);

	//LUL
	hookLength = 7;
	hookAddress = 0x14028D4F1;
	bRemoAddTest = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fRemoAddTest, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//open console
	hookLength = 7;
	hookAddress = 0x140627AFE;
	bOpenLogConsole = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fOpenLogConsole, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//FreeCam
	hookLength = 7;
	hookAddress = 0x14024DF91;
	bFreeCam = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)fFreeCam, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//leave commented out
	/*if (!VirtualProtect((LPVOID)0x14024EB29, 6, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14024EB29, freeCamPatch, 6);
	VirtualProtect((LPVOID)0x14024EB29, 6, oldProtect, &oldProtect);*/

	//more freecam
	/*hookLength = 5;
	hookAddress = 0x1400C5FD4;
	bGetFreeCamMode1 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tGetFreeCamMode1, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14024EB21;
	bGetFreeCamMode2 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tGetFreeCamMode2, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14024EFA2;
	bGetFreeCamMode3 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tGetFreeCamMode3, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14024F1C7;
	bGetFreeCamMode4 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tGetFreeCamMode4, 0);
	MH_EnableHook((LPVOID)hookAddress);*/

	//L3 + R3 Exit
	hookLength = 5;
	hookAddress = 0x14024B07B;
	bExitButtonComboCheck1 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tExitButtonComboCheck1, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14025622C;
	bExitButtonComboCheck2 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tExitButtonComboCheck2, 0);
	MH_EnableHook((LPVOID)hookAddress);

	hookLength = 5;
	hookAddress = 0x14027AF42;
	bExitButtonComboCheck3 = hookAddress + hookLength;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tExitButtonComboCheck3, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//slow down DbgCamera movement (0.25 multiplier instead of 0.5)
	VirtualProtect((LPVOID)0x14019C1F2, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14019C1F2, dbgCamZSpeedPatch, 4);
	VirtualProtect((LPVOID)0x14019C1F2, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x14019C3EC, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14019C3EC, dbgCamYSpeedPatch, 4);
	VirtualProtect((LPVOID)0x14019C3EC, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x14019C2E2, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14019C2E2, dbgCamXSpeedPatch, 4);
	VirtualProtect((LPVOID)0x14019C2E2, 4, oldProtect, &oldProtect);

	puts("Patching done");
}

void AddPatches()
{
	DWORD oldProtect;
	uint64_t offset = 0;
	long long hookAddress;
	BYTE patch = 0x60;
	//AddCOPYPatch(0x14080A2F0, mov1ToAlBytes, 2, 0xC0, 1);
	//AddCOPYPatch(0x14080A2E0, mov1ToAlBytes, 2, 0xC0, 1);
	//AddCOPYPatch(0x140E82DEE, xorRaxBytes, 5, 1, 1);
	//AddCOPYPatch(0x14062C3AE, pFreeCamBytes1, 5, 0, 1);
	//AddCOPYPatch(0x14062C401, pFreeCamBytes2, 31, 0, 1); //doesnt work, but not causing crash
	//AddCOPYPatch(0x1408D8049, mov1ToAlBytes, 5, 0xFF); //remove
	//AddCOPYPatch(0x1408B1CF1, dBypassCheck1, 4, 1, 1);
	//AddCOPYPatch(0x140EE7C01, dBypassCheck2, 4, 4);
	//AddCOPYPatch(0x140EC365F, systemPropertiesValue, 1, 1, 1);
	//AddHOOKPatch(0x14080905B, 7, 0xF5, &tLoadGameProperties, &bLoadGameProperties, 1);
	//hookAddress = 0x1408E4C2F;
	//fuckshitshit = VirtualAllocEx(hProcessSHIT, (LPVOIDc )0x140000000, 20, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	//DWORD fuck = GetLastError();
	
	//int hookLength = 5;
	//hookAddress = 0x140322B92;
	//bExitButtonComboCheck2 = hookAddress + hookLength;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)fGetDebugMenuLabelNode, 0);
	//MH_EnableHook((LPVOID)hookAddress);
	
	//haha = (LPVOID*)(0x140322B93 + *(int*)0x140322B93);
	hookAddress = 0x140136C60;
	bAntiTamperSkip = 0x142A0EA9B;
	MH_CreateHook((LPVOID)hookAddress, (LPVOID)tPatchGame, 0);
	MH_EnableHook((LPVOID)hookAddress);

	//increase lua memory
	unsigned int patchy = 0x9C4000;

	VirtualProtect((LPVOID)0x140168312, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x140168312, &patchy, 4);
	VirtualProtect((LPVOID)0x140168312, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x140168339, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x140168339, &patchy, 4);
	VirtualProtect((LPVOID)0x140168339, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x14016837B, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14016837B, &patchy, 4);
	VirtualProtect((LPVOID)0x14016837B, 4, oldProtect, &oldProtect);

	//increase debug memory
	VirtualProtect((LPVOID)0x140168891, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x140168891, &debugMem, 4);
	VirtualProtect((LPVOID)0x140168891, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x1401688B8, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1401688B8, &debugMem, 4);
	VirtualProtect((LPVOID)0x1401688B8, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x1401688FE, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1401688FE, &debugMem, 4);
	VirtualProtect((LPVOID)0x1401688FE, 4, oldProtect, &oldProtect);

	return;

	//memcpy(fuckshitshit, getDbgMenuLabelNodeFunc, 20);
	//skip over anti-tamper code integrity bullshit
	//made obsolete by patch below
	VirtualProtect((LPVOID)0x140990556, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(int*)0x140990556 = 0x23E2438;
	VirtualProtect((LPVOID)0x140990556, 4, oldProtect, &oldProtect);
	

	/*VirtualProtect((LPVOID)0x142B5D613, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(int*)0x142B5D613 = 0xA7DC35;
	VirtualProtect((LPVOID)0x142B5D613, 4, oldProtect, &oldProtect);*/
	/*VirtualProtect((LPVOID)0x14270FE2F, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(int*)0x14270FE2F = 0x6C158;
	VirtualProtect((LPVOID)0x14270FE2F, 4, oldProtect, &oldProtect);*/
	//doesn't work maybe
	/*VirtualProtect((LPVOID)0x142B5D613, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(int*)0x142B5D613 = 0xFD5D9673;
	VirtualProtect((LPVOID)0x142B5D613, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x14007ACF0, 10, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14007ACF0, we_patch, 10);
	VirtualProtect((LPVOID)0x14007ACF0, 10, oldProtect, &oldProtect);*/

	//jump over all the anti-tamper stuff lmao
	VirtualProtect((LPVOID)0x140136C61, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(int*)0x140136C61 = 0x28D7E36;
	VirtualProtect((LPVOID)0x140136C61, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	
	


	//exception filter stuff. useless? not useless
	VirtualProtect((LPVOID)0x1420B52F0, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(uint64_t*)0x1420B52F0 = 0x140152AF0;
	VirtualProtect((LPVOID)0x1420B52F0, 8, PAGE_EXECUTE_READWRITE, &oldProtect);


	//pointless, patching out the fixing
	/*VirtualProtect((LPVOID)0x14279102D, 3, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((LPVOID)0x14279102D, navi_patch2, 3);
	VirtualProtect((LPVOID)0x14279102D, 3, PAGE_EXECUTE_READWRITE, &oldProtect);

	VirtualProtect((LPVOID)0x142A4410C, 3, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((LPVOID)0x142A4410C, navi_patch2, 3);
	VirtualProtect((LPVOID)0x142A4410C, 3, PAGE_EXECUTE_READWRITE, &oldProtect);

	VirtualProtect((LPVOID)0x1424B2371, 3, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((LPVOID)0x1424B2371, navi_patch2, 3);
	VirtualProtect((LPVOID)0x1424B2371, 3, PAGE_EXECUTE_READWRITE, &oldProtect);*/
	return;
	for (int i = 0; i < 26; i++)
	{
		//AddHOOKPatch(getDbgMenuLabelNodeFuncCalls[i], 5, getDbgMenuLabelNodeFuncCallsLastByte[i], &fGetDebugMenuLabelNode, NULL, 0, true);

		/*while (*(BYTE*)getDbgMenuLabelNodeFuncCalls[i] != 0xE8);
		MH_CreateHook((LPVOID)getDbgMenuLabelNodeFuncCalls[i], (LPVOID)fGetDebugMenuLabelNode, 0);
		MH_EnableHook((LPVOID)getDbgMenuLabelNodeFuncCalls[i]);
		*(BYTE*)getDbgMenuLabelNodeFuncCalls[i] = 0xE8;*/

		//uint64_t offset = getDbgMenuLabelNodeFuncCalls[i] + 1;
		//VirtualProtect((LPVOID)offset, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
		////memcpy((void*)offset, &fDrawDebugMenu, 8);
		//int diff = (uint64_t)haha - offset - 4;
		//*(int*)offset = diff;
		//VirtualProtect((LPVOID)offset, 4, oldProtect, &oldProtect);
	}

	//patch dbg menu control/drawing members

	for (int i = 0; i < 106; i++)
	{
		offset = dbgMenuControlVtableOffsets[i];
		VirtualProtect((LPVOID)offset, 16, PAGE_EXECUTE_READWRITE, &oldProtect);
		//memcpy((void*)offset, &fDrawDebugMenu, 8);
		*(uint64_t*)offset = (uint64_t)fControlDebugMenu;
		*(uint64_t*)(offset + 8) = (uint64_t)fDrawDebugMenu;
		VirtualProtect((LPVOID)offset, 16, oldProtect, &oldProtect);
	}

	//patch in new dbgMenuGetLabelNode
	//AddCOPYPatch(0x1408E4C2F, getDbgMenuLabelNodeFunc, 20, 0x4E);
	
	//AddCOPYPatch(0x14015E33B, backgroundPatch, 7, 0x01);
	////AddCOPYPatch(0x1408E4C43, initDbgMenuPatch, 30, 0); //change later
	//AddHOOKPatch(0x140152A38, 5, 0xC3, &fInitRootDbgMenuLabelNode, NULL);

	////AddCOPYPatch(0x140152A38, initDbgMenuPatchJump, 5, 0xC3);
	//AddCOPYPatch(0x14015E594, (BYTE*)&ezDrawDbgMenuBufferSize, 4, 0);
	//AddHOOKPatch(0x1401B67F3, 7, 1, &tLoadGamePropertiesOrSth, &bLoadGamePropertiesOrSth);
	//AddCOPYPatch(0x1402773F7, boot_patch, 4, 0xFF);
	//AddCOPYPatch(0x1401E8EBF, (BYTE*)&blendstate_patch, 1, 2);
	//AddCOPYPatch(0x140168312, (BYTE*)&luamem_patch, 4, 0);
	//AddCOPYPatch(0x140168339, (BYTE*)&luamem_patch, 4, 0);
	//AddCOPYPatch(0x14016837B, (BYTE*)&luamem_patch, 4, 0);

	////load game.properties
	//AddHOOKPatch(0x14025E10B, 7, 0xAB, &tLoadGameProperties, &bLoadGameProperties);

	////under construction
	//AddHOOKPatch(0x140522043, 6, 0x01, &fAddUnderConstructionParamMan, &bAddUnderConstructionParamMan);
	//AddHOOKPatch(0x1407C3576, 10, 0xAA, &fAddUnderConstructionEmevdMan, &bAddUnderConstructionEmevdMan);

	////1432AEAB8 init
	//AddHOOKPatch(0x1432AEAB8, 5, 0xE9, &loadEnemyMsbName, &whatever);
	//
	//AddHOOKPatch(0x140175075, 6, 0, &writePlayerName, &whatever);

	////1422847E1 free
	//AddHOOKPatch(0x1422847E1, 5, 0x32, &freeEnemyMsbName, &whatever);

	////draw dbg menu
	//AddHOOKPatch(0x14015BE2A, 10, 0, &tDrawDebugMenuGOGOGO, &bDrawDebugMenuGOGOGO);

	////fix strings
	//AddCOPYPatch(0x14131D2A0, fullCircleUTF16, 4, 0x20);
	//AddCOPYPatch(0x14131C668, emptyCircleUTF16, 4, 0x20);

	////patch gesture menu button combo
	//AddCOPYPatch(0x1401A3435, (BYTE*)&gesturecombo_patch, 1, 0x75);
	//AddCOPYPatch(0x1401A3447, (BYTE*)&gesturecombo_patch, 1, 0x75);
	//AddCOPYPatch(0x1401A3449, gestureMenuPatch, 32, 0);



	////LoadBootSettings();

	////restore debug dash
	//AddHOOKPatch(0x140370122, 5, 0x08, &tCheckDebugDash, &bCheckDebugDash);
	//AddCOPYPatch(0x141D151DA, (BYTE*)&debugdashenable_patch, 1, 0);

	//offset = 0x141AC56D8;

	//VirtualProtect((LPVOID)offset, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	//*(uint64_t*)offset = (uint64_t)fDbgDispLoading;
	//VirtualProtect((LPVOID)offset, 8, oldProtect, &oldProtect);

	//AddHOOKPatch(0x1402CD384, 8, 0, &tEzDrawAddDrawPlans1, &bEzDrawAddDrawPlans1);
	//AddHOOKPatch(0x1402CD626, 8, 0, &tEzDrawAddDrawPlans2, &bEzDrawAddDrawPlans2);
	//AddHOOKPatch(0x1402CD851, 8, 0, &tEzDrawAddDrawPlans3, &bEzDrawAddDrawPlans3);
	//AddHOOKPatch(0x1402CDAE7, 8, 0, &tEzDrawAddDrawPlans4, &bEzDrawAddDrawPlans4);
	//AddHOOKPatch(0x1402CDD92, 8, 0, &tEzDrawAddDrawPlans5, &bEzDrawAddDrawPlans5);
	//AddHOOKPatch(0x1402CF099, 5, 0, &tEzDrawAddDrawPlans6, &bEzDrawAddDrawPlans6);
	//AddHOOKPatch(0x14027993A, 7, 0x01, &fApplySettingsDamageMan, &bApplySettingsDamageMan);
	//AddHOOKPatch(0x14036E3D6, 5, 0xFF, &fApplySettingsWorldChrManDbg, &bApplySettingsWorldChrManDbg);

	////meow patch for m99 ffxbnd
	//AddCOPYPatch(0x1404FA954, dbg_patch, 6, 0);

	////LUL
	//AddHOOKPatch(0x14028D4F1, 7, 0, &fRemoAddTest, &bRemoAddTest);

	////open console
	//AddHOOKPatch(0x140627AFE, 7, 0, &fOpenLogConsole, &bOpenLogConsole);

	////FreeCam
	//AddHOOKPatch(0x14024DF91, 7, 0x70, &fFreeCam, &bFreeCam);

	////L3 + R3 Exit
	//AddHOOKPatch(0x14024B07B, 5, 0xFF, &tExitButtonComboCheck1, &bExitButtonComboCheck1);
	//AddHOOKPatch(0x14025622C, 5, 0xFF, &tExitButtonComboCheck2, &bExitButtonComboCheck2);
	//AddHOOKPatch(0x14027AF42, 5, 0xFF, &tExitButtonComboCheck3, &bExitButtonComboCheck3);

	////slow down DbgCamera movement (0.25 multiplier instead of 0.5)
	//AddCOPYPatch(0x14019C1F2, dbgCamZSpeedPatch, 4, 0x01);
	//AddCOPYPatch(0x14019C3EC, dbgCamYSpeedPatch, 4, 0x01);
	//AddCOPYPatch(0x14019C2E2, dbgCamXSpeedPatch, 4, 0x01);
}

BOOL WINAPI DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

	static HMODULE dinput8dll = nullptr;
	DWORD oldProtect;
	long long hookAddress = 0;
	HANDLE ini;
	HMODULE chainModule = NULL;
	wchar_t chainPath[MAX_PATH];
	wchar_t dllPath[MAX_PATH];
	FILE* fp = NULL;

	//InitUnhandledExceptionFilter();

    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH:
	{
		AllocConsole();
		freopen_s(&fp, "CONIN$", "r", stdin);
		freopen_s(&fp, "CONOUT$", "w", stdout);
		HANDLE ini;

		//i only need this for esd log... its silly af
		hProcessSHIT = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcIdSHIT(L"DarkSoulsRemastered.exe"));
		
		puts("DSR Debug Menu v1.5");
		printf("Opening debug.ini...");

		if ((ini = CreateFile(L"debug.ini", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
		{
			CloseHandle(ini);

			printf("success\n");

			GetPrivateProfileStringW(L"Misc", L"dinput8DllWrapper", L"", chainPath, MAX_PATH, L".\\debug.ini");

		}
		else 
		{
			printf("fail\n");
		}

		if (chainPath && wcscmp(chainPath, L""))
		{
			GetCurrentDirectoryW(MAX_PATH, dllPath);
			wcscat_s(dllPath, MAX_PATH, L"\\");
			wcscat_s(dllPath, MAX_PATH, chainPath);
			chainModule = LoadLibraryW(dllPath);

			if (chainModule)
			{
				wprintf(L"Chaining %s\n", dllPath);
				oDirectInput8Create = (tDirectInput8Create)GetProcAddress(chainModule, "DirectInput8Create");
			}
		}

		if (!chainModule)
		{
			wchar_t path[MAX_PATH];
			GetSystemDirectoryW(path, MAX_PATH);
			wcscat_s(path, MAX_PATH, L"\\dinput8.dll");
			dinput8dll = LoadLibraryW(path);

			if (dinput8dll)
			{
				oDirectInput8Create = (tDirectInput8Create)GetProcAddress(dinput8dll, "DirectInput8Create");
			}
		}

		MH_Initialize();
		AddPatches();


		break;
	}
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		if (chainModule)
		{
			FreeLibrary(chainModule);
		}
		else if (dinput8dll)
		{
			FreeLibrary(dinput8dll);
		}
		if (hProcessSHIT)
			CloseHandle(hProcessSHIT);
		FreeConsole();

		if (fp)
			fclose(fp);

        break;
    }
    return TRUE;
}

//HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
//{
//	if (!m_pDirectInput8Create)
//	{
//		return E_FAIL;
//	}
//
//	HRESULT hr = m_pDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
//
//	if (SUCCEEDED(hr))
//	{
//		genericQueryInterface(riidltf, ppvOut);
//	}
//
//	return hr;
//}
//
//HRESULT WINAPI DllCanUnloadNow()
//{
//	if (!m_pDllCanUnloadNow)
//	{
//		return E_FAIL;
//	}
//
//	return m_pDllCanUnloadNow();
//}
//
//HRESULT WINAPI DllGetClassObject(IN REFCLSID rclsid, IN REFIID riid, OUT LPVOID FAR* ppv)
//{
//	if (!m_pDllGetClassObject)
//	{
//		return E_FAIL;
//	}
//
//	HRESULT hr = m_pDllGetClassObject(rclsid, riid, ppv);
//
//	if (SUCCEEDED(hr))
//	{
//		genericQueryInterface(riid, ppv);
//	}
//
//	return hr;
//}
//
//HRESULT WINAPI DllRegisterServer()
//{
//	if (!m_pDllRegisterServer)
//	{
//		return E_FAIL;
//	}
//
//	return m_pDllRegisterServer();
//}
//
//HRESULT WINAPI DllUnregisterServer()
//{
//	if (!m_pDllUnregisterServer)
//	{
//		return E_FAIL;
//	}
//
//	return m_pDllUnregisterServer();
//}
//
//LPCDIDATAFORMAT WINAPI GetdfDIJoystick()
//{
//	if (!m_pGetdfDIJoystick)
//	{
//		return nullptr;
//	}
//
//	return m_pGetdfDIJoystick();
//}

DWORD GetProcIdSHIT (const wchar_t* procname)
{
	PROCESSENTRY32 pe;
	HANDLE hSnap;
	pe.dwSize = sizeof(PROCESSENTRY32);
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(hSnap, &pe)) {
		do {
			if (wcscmp(pe.szExeFile, procname) == 0) {
				break;
			}
		} while (Process32Next(hSnap, &pe));
	}
	return pe.th32ProcessID;
}