#pragma once

#define INITGUID

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <TlHelp32.h>

class m_IDirectInput8A;
class m_IDirectInput8W;
class m_IDirectInputDevice8A;
class m_IDirectInputDevice8W;
class m_IDirectInputEffect;

#include "AddressLookupTable.h"
//#include "Common\Logging.h"
#include "MinHook/include/MinHook.h"

//#include "Menu.h"

typedef HRESULT(WINAPI *DirectInput8CreateProc)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
typedef HRESULT(WINAPI *DllCanUnloadNowProc)();
typedef	HRESULT(WINAPI *DllGetClassObjectProc)(REFCLSID, REFIID, LPVOID *);
typedef HRESULT(WINAPI *DllRegisterServerProc)();
typedef HRESULT(WINAPI *DllUnregisterServerProc)();
typedef	LPCDIDATAFORMAT(WINAPI *GetdfDIJoystickProc)();

void genericQueryInterface(REFIID CalledID, LPVOID * ppvObj);
extern AddressLookupTable<void> ProxyAddressLookupTable;

#include "IDirectInput8A.h"
#include "IDirectInput8W.h"
#include "IDirectInputDevice8A.h"
#include "IDirectInputDevice8W.h"
#include "IDirectInputEffect.h"
#include "IDirectInputEnumDevice.h"
#include "IDirectInputEnumEffect.h"
#include "IClassFactory.h"

extern "C" VOID fGetCameraObj();
extern "C" DWORD64 bGetCameraObj;
extern "C" VOID fGetCameraObjAlt();
extern "C" DWORD64 bGetCameraObjAlt;
extern "C" VOID fSetCameraObj();
extern "C" DWORD64 bSetCameraObj;
extern "C" VOID tLoadGameProperties();
extern "C" DWORD64 bLoadGameProperties;
extern "C" VOID loadEnemyMsbName();
extern "C" VOID freeEnemyMsbName();
extern "C" VOID LoadGameProperties();
extern "C" VOID fDrawDebugMenu();
extern "C" VOID fControlDebugMenu();
extern "C" VOID fDrawDebugMenuGOGOGO();
extern "C" VOID tDrawDebugMenuGOGOGO();
extern "C" VOID tCheckDebugDash();
extern "C" DWORD64 bDrawDebugMenuGOGOGO;
extern "C" DWORD64 bDebugMemAlloc;
extern "C" VOID fDebugMemAlloc();
extern "C" DWORD64 fDisableDebugMemHook;
extern "C" DWORD64 bWritePlayerName;
extern "C" VOID writePlayerName();
extern "C" DWORD64 bContinueInitPlayer;
extern "C" DWORD64 bCheckDebugDash;
extern "C" VOID fDbgDispLoading();

extern "C" DWORD64 bOpenLogConsole;

extern "C" DWORD64 bEzDrawAddDrawPlans1;
extern "C" DWORD64 bEzDrawAddDrawPlans2;
extern "C" DWORD64 bEzDrawAddDrawPlans3;
extern "C" DWORD64 bEzDrawAddDrawPlans4;
extern "C" DWORD64 bEzDrawAddDrawPlans5;
extern "C" DWORD64 bEzDrawAddDrawPlans6;
extern "C" VOID tEzDrawAddDrawPlans1();
extern "C" VOID tEzDrawAddDrawPlans2();
extern "C" VOID tEzDrawAddDrawPlans3();
extern "C" VOID tEzDrawAddDrawPlans4();
extern "C" VOID tEzDrawAddDrawPlans5();
extern "C" VOID tEzDrawAddDrawPlans6();

extern "C" DWORD64 bApplySettingsDamageMan;
extern "C" DWORD64 bApplySettingsWorldChrManDbg;
extern "C" VOID fApplySettingsDamageMan();
extern "C" VOID fApplySettingsWorldChrManDbg();
extern "C" DWORD64 pSettingsDamageMan;
extern "C" DWORD64 pSettingsWorldChrManDbg;

extern "C" DWORD textHighlightColor;

extern "C" VOID fOpenLogConsole();

extern "C" DWORD64 bRemoAddTest;
extern "C" VOID fRemoAddTest();

extern "C" DWORD64 bAddUnderConstructionParamMan;
extern "C" VOID fAddUnderConstructionParamMan();
extern "C" DWORD64 bAddUnderConstructionEmevdMan;
extern "C" VOID fAddUnderConstructionEmevdMan();

extern "C" DWORD64 bFreeCam;
extern "C" DWORD64 bGetFreeCamMode1;
extern "C" DWORD64 bGetFreeCamMode2;
extern "C" DWORD64 bGetFreeCamMode3;
extern "C" DWORD64 bGetFreeCamMode4;
extern "C" VOID fFreeCam();
extern "C" VOID tGetFreeCamMode1();
extern "C" VOID tGetFreeCamMode2();
extern "C" VOID tGetFreeCamMode3();
extern "C" VOID tGetFreeCamMode4();

extern "C" DWORD64 bExitButtonComboCheck1;
extern "C" DWORD64 bExitButtonComboCheck2;
extern "C" DWORD64 bExitButtonComboCheck3;
extern "C" VOID tExitButtonComboCheck1();
extern "C" VOID tExitButtonComboCheck2();
extern "C" VOID tExitButtonComboCheck3();
