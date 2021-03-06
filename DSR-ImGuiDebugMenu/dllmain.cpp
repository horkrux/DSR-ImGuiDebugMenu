#include "dinput8.h"
#include "d3d11hook.h"
#include "DbgSettings.h"
#include "Globals.h"
#include <locale.h>

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

HANDLE imguiThread;
bool notifyEnd = false;

const LPCWSTR AppWindowTitle = L"DARK SOULS™: REMASTERED"; // Targeted D11 Application Window Title.
//const LPCWSTR AppWindowTitle = L"DARK SOULS III";
HWND g_hWnd = NULL;
AddressLookupTable<void> ProxyAddressLookupTable = AddressLookupTable<void>();

DirectInput8CreateProc m_pDirectInput8Create;
DllCanUnloadNowProc m_pDllCanUnloadNow;
DllGetClassObjectProc m_pDllGetClassObject;
DllRegisterServerProc m_pDllRegisterServer;
DllUnregisterServerProc m_pDllUnregisterServer;
GetdfDIJoystickProc m_pGetdfDIJoystick;

BYTE patching_system[2] = { 0xB0, 0x01 };
BYTE boot_patch[4] = { 0x55, 0x67, 0xFE, 0xFF };
BYTE dbg_patch[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
BYTE navi_patch[6] = { 0xE9, 0xA5, 0x05, 0x00, 0x00, 0x90 };
BYTE navi_patch2[9] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
BYTE navi_patch3[8] = { 0xE9, 0x86, 0x0D, 0x00, 0x00, 0x90, 0x90, 0x90 };

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


BYTE getDbgMenuLabelNodeFunc[20] = { 0x48, 0xA1, 0xC8, 0x4C, 0xC0, 0x41, 0x01, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC0, 0x74, 0x04, 0x48, 0x8B, 0x40, 0x08, 0xC3 };

uint64_t getDbgMenuLabelNodeFuncCalls[26] = { 0x1400F7EE6, 0x14015B127, 0x14015B131, 0x14015C134, 0x14015C13E, 0x140257786, 0x140257797, 0x140257DF1, 0x140257DFF, 0x1402C34EA, 0x1402C34F8, 0x14044B85B, 
											  0x14044B869, 0x140516A3B, 0x140516A45, 0x140516AFA, 0x140516B04, 0x14059FD85, 0x14059FD93, 0x140779CA5, 0x140779CB3, 0x1407E7F8B, 0x1407ED21E, 0x1407F5A15,
											  0x1407F5A23, 0x1407F61D5 };

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

unsigned int ezDrawDbgMenuBufferSize = 0x3000;

//int ApplyPatches()
//{
//	BYTE test_byte;
//
//	ReadProcessMemory(hProcess, (LPVOID)0x140374E0B, &test_byte, 1, NULL);
//
//	if (test_byte != 0x90)
//		WriteProcessMemory(hProcess, (LPVOID)0x140374E0B, dbg_patch, 6, NULL);
//
//	ReadProcessMemory(hProcess, (LPVOID)0x14015CF6A, &test_byte, 1, NULL);
//
//	if (test_byte != 0x60)
//	{
//		BYTE patch = 0x60;
//
//		WriteProcessMemory(hProcess, (LPVOID)0x14015CF6A, &patch, 1, NULL);
//	}
//
//	ReadProcessMemory(hProcess, (LPVOID)0x140214924, &test_byte, 1, NULL);
//
//	if (test_byte == 0x8B)
//	{
//		int hookLength = 6;
//		long long hookAddress = 0x140214924;
//		bGetCameraObj = hookAddress + hookLength;
//		MH_CreateHook((LPVOID)hookAddress, (LPVOID)fGetCameraObj, 0);
//		MH_EnableHook((LPVOID)hookAddress);
//
//		/*hookLength = 6;
//		hookAddress = 0x14021E734;
//		bGetCameraObjAlt = hookAddress + hookLength;
//		MH_CreateHook((LPVOID)hookAddress, (LPVOID)fGetCameraObjAlt, 0);
//		MH_EnableHook((LPVOID)hookAddress);*/
//
//		hookLength = 7;
//		hookAddress = 0x1401E05B3;
//		bSetCameraObj = hookAddress + hookLength;
//		MH_CreateHook((LPVOID)hookAddress, (LPVOID)fSetCameraObj, 0);
//		MH_EnableHook((LPVOID)hookAddress);
//		//Hook((void*)hookAddress, fGetCameraObj, hookLength);
//	}
//
//	ReadProcessMemory(hProcess, (LPVOID)0x1402773F7, &test_byte, 1, NULL);
//
//	if (test_byte != 0x55)
//	{
//		WriteProcessMemory(hProcess, (LPVOID)0x1402773F7, boot_patch, 4, NULL);
//	}
//
//	ReadProcessMemory(hProcess, (LPVOID)0x1401E8EBF, &test_byte, 1, NULL);
//
//	if (test_byte == 0x2)
//	{
//		BYTE patch = 3;
//		WriteProcessMemory(hProcess, (LPVOID)0x1401E8EBF, &patch, 1, NULL);
//	}
//}

void DisableDebugMemHook()
{
	MH_DisableHook((LPVOID)0x14017651B);
}

DWORD64 fDisableDebugMemHook = (DWORD64)&DisableDebugMemHook;

void UndoDebugMemoryChanges()
{
	unsigned int debugMem = 0x200000;

	*(unsigned int*)0x140168891 = debugMem;
	*(unsigned int*)0x1401688B8 = debugMem;
	*(unsigned int*)0x1401688FE = debugMem;

	/*VirtualProtect((LPVOID)0x140168891, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x140168891, &debugMem, 4);
	VirtualProtect((LPVOID)0x140168891, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x1401688B8, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1401688B8, &debugMem, 4);
	VirtualProtect((LPVOID)0x1401688B8, 4, oldProtect, &oldProtect);

	VirtualProtect((LPVOID)0x1401688FE, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x1401688FE, &debugMem, 4);
	VirtualProtect((LPVOID)0x1401688FE, 4, oldProtect, &oldProtect);*/
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

	/*if (!VirtualProtect((LPVOID)0x14024EB29, 6, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;
	memcpy((void*)0x14024EB29, freeCamPatch, 6);
	VirtualProtect((LPVOID)0x14024EB29, 6, oldProtect, &oldProtect);*/

	//more freecam
	hookLength = 5;
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
	MH_EnableHook((LPVOID)hookAddress);

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

DWORD WINAPI MainThread(HMODULE hModule)
{
	while (!g_hWnd)
		g_hWnd = FindWindow(0, AppWindowTitle);
	
	ApplyPatches();
	ImplHookDX11_Init(hModule, g_hWnd); 

	return S_OK;
}


BOOL WINAPI DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

	static HMODULE dinput8dll = nullptr;
	DWORD oldProtect;
	unsigned int debugMem = 0x1000000;
	long long hookAddress = 0;
	HANDLE ini;
	HMODULE chainModule = NULL;
	wchar_t chainPath[MAX_PATH];
	wchar_t dllPath[MAX_PATH];

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

		HANDLE ini;
		if ((ini = CreateFile(L"game.properties", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
		{
			CloseHandle(ini);

			GetPrivateProfileStringW(L"Misc", L"dinput8DllWrapper", L"", chainPath, MAX_PATH, L".\\game.properties");

			bool isMouseDisabled = GetPrivateProfileInt(L"Core", L"Option.Control.DisableMouse", 0, L"./game.properties");

			g_isDisableMouse = isMouseDisabled;

		}

		if (chainPath && wcscmp(chainPath, L""))
		{
			GetCurrentDirectoryW(MAX_PATH, dllPath);
			wcscat_s(dllPath, MAX_PATH, L"\\");
			wcscat_s(dllPath, MAX_PATH, chainPath);
			chainModule = LoadLibraryW(dllPath);

			if (chainModule)
			{
				// Get function addresses
				m_pDirectInput8Create = (DirectInput8CreateProc)GetProcAddress(chainModule, "DirectInput8Create");
				m_pDllCanUnloadNow = (DllCanUnloadNowProc)GetProcAddress(chainModule, "DllCanUnloadNow");
				m_pDllGetClassObject = (DllGetClassObjectProc)GetProcAddress(chainModule, "DllGetClassObject");
				m_pDllRegisterServer = (DllRegisterServerProc)GetProcAddress(chainModule, "DllRegisterServer");
				m_pDllUnregisterServer = (DllUnregisterServerProc)GetProcAddress(chainModule, "DllUnregisterServer");
				m_pGetdfDIJoystick = (GetdfDIJoystickProc)GetProcAddress(chainModule, "GetdfDIJoystick");
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
				// Get function addresses
				m_pDirectInput8Create = (DirectInput8CreateProc)GetProcAddress(dinput8dll, "DirectInput8Create");
				m_pDllCanUnloadNow = (DllCanUnloadNowProc)GetProcAddress(dinput8dll, "DllCanUnloadNow");
				m_pDllGetClassObject = (DllGetClassObjectProc)GetProcAddress(dinput8dll, "DllGetClassObject");
				m_pDllRegisterServer = (DllRegisterServerProc)GetProcAddress(dinput8dll, "DllRegisterServer");
				m_pDllUnregisterServer = (DllUnregisterServerProc)GetProcAddress(dinput8dll, "DllUnregisterServer");
				m_pGetdfDIJoystick = (GetdfDIJoystickProc)GetProcAddress(dinput8dll, "GetdfDIJoystick");
			}
		}

		//disable mouse early
		/*if ((ini = CreateFile(L"game.properties", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
		{
			CloseHandle(ini);
			bool isMouseDisabled = GetPrivateProfileInt(L"Core", L"Option.Control.DisableMouse", 0, L"./game.properties");

			g_isDisableMouse = isMouseDisabled;
		}*/

		

		//increase debug memory
		if (!VirtualProtect((LPVOID)0x140168891, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
			return false;
		memcpy((void*)0x140168891, &debugMem, 4);
		VirtualProtect((LPVOID)0x140168891, 4, oldProtect, &oldProtect);

		if (!VirtualProtect((LPVOID)0x1401688B8, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
			return false;
		memcpy((void*)0x1401688B8, &debugMem, 4);
		VirtualProtect((LPVOID)0x1401688B8, 4, oldProtect, &oldProtect);

		if (!VirtualProtect((LPVOID)0x1401688FE, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
			return false;
		memcpy((void*)0x1401688FE, &debugMem, 4);
		VirtualProtect((LPVOID)0x1401688FE, 4, oldProtect, &oldProtect);

		//Sleep(10000);
		//ApplyPatches();
		MH_Initialize();

		//restore old debug memory allocation code
		hookAddress = 0x14017651B;
		bDebugMemAlloc = hookAddress + 5;
		MH_CreateHook((LPVOID)hookAddress, (LPVOID)fDebugMemAlloc, 0);
		MH_EnableHook((LPVOID)hookAddress);

		imguiThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);

		//InitSettings();
		

		break;
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
		notifyEnd = true;
		WaitForSingleObject(imguiThread, INFINITE);
		//FreeLibrary(dinput8dll);
        break;
    }
    return TRUE;
}

HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
	if (!m_pDirectInput8Create)
	{
		return E_FAIL;
	}

	HRESULT hr = m_pDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(riidltf, ppvOut);
	}

	return hr;
}

HRESULT WINAPI DllCanUnloadNow()
{
	if (!m_pDllCanUnloadNow)
	{
		return E_FAIL;
	}

	return m_pDllCanUnloadNow();
}

HRESULT WINAPI DllGetClassObject(IN REFCLSID rclsid, IN REFIID riid, OUT LPVOID FAR* ppv)
{
	if (!m_pDllGetClassObject)
	{
		return E_FAIL;
	}

	HRESULT hr = m_pDllGetClassObject(rclsid, riid, ppv);

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(riid, ppv);
	}

	return hr;
}

HRESULT WINAPI DllRegisterServer()
{
	if (!m_pDllRegisterServer)
	{
		return E_FAIL;
	}

	return m_pDllRegisterServer();
}

HRESULT WINAPI DllUnregisterServer()
{
	if (!m_pDllUnregisterServer)
	{
		return E_FAIL;
	}

	return m_pDllUnregisterServer();
}

LPCDIDATAFORMAT WINAPI GetdfDIJoystick()
{
	if (!m_pGetdfDIJoystick)
	{
		return nullptr;
	}

	return m_pGetdfDIJoystick();
}