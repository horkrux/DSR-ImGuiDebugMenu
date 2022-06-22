#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <stdio.h>
#include <wingdi.h>

#include "dinput8/dinputWrapper.h"
#include "MinHook/include/MinHook.h"

extern "C" wchar_t paramdefbndPathString[] = L"paramdef:/paramdef.paramdefbnd";
extern "C" wchar_t gamePropertiesPathString[] = L"config:/gametest.properties";
extern "C" wchar_t textHighlightColorRStr[] = L"DbgMenu.Def.TextHighlightColor.R";
extern "C" wchar_t textHighlightColorGStr[] = L"DbgMenu.Def.TextHighlightColor.G";
extern "C" wchar_t textHighlightColorBStr[] = L"DbgMenu.Def.TextHighlightColor.B";
extern "C" wchar_t textHighlightColorAStr[] = L"DbgMenu.Def.TextHighlightColor.A";
extern "C" wchar_t damageManDebugBallDisplayStr[] = L"DamageMan.DebugBallDisplay";
extern "C" wchar_t damageManDebugInfoDisplayStr[] = L"DamageMan.DebugInfoDisplay";
extern "C" wchar_t damageManDamageWpnPolyStr[] = L"DamageMan.DamageWpnPoly";
extern "C" wchar_t damageManDamageAtkParamRefStr[] = L"DamageMan.DamageAtkParamRef";
extern "C" wchar_t DebugDashSwitchStr[] = L"GameData.DebugDashSwitch";
extern "C" wchar_t rootString[] = L"ROOT";

extern "C" DWORD textHighlightColor4[4];

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
extern "C" VOID tEsdDbgLogOutput();
extern "C" DWORD64 fPrintDbgLog;

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
extern "C" VOID tApplySettingsDamageMan();
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

extern "C" DWORD64 bLoadGamePropertiesOrSth;
extern "C" VOID tLoadGamePropertiesOrSth();
extern "C" VOID fGetDebugMenuLabelNode();
extern "C" VOID fInitRootDbgMenuLabelNode();

extern "C" DWORD64 bAntiTamperSkip;
extern "C" DWORD64 fPatchGame;
extern "C" VOID tPatchGame();

extern "C" VOID tLoadParamdefbnd();
extern "C" DWORD64 bLoadParamdefbnd;

extern "C" VOID tLoadDbgMenuTextHighlightColor();
extern "C" DWORD64 bLoadDbgMenuTextHighlightColor;
extern "C" DWORD64 fConvertColor;

void PrintText(DWORD64, char*);
VOID PrintDbgLog(wchar_t*, char*, byte*);

//typedef enum {
//	INVALID,
//	HOOK,
//	HOOKCALL,
//	COPY
//} PATCHJOB_TYPE;

typedef enum {
	HOOK,
	HOOKCALL,
	COPY
} GAMEPATCH_TYPE;

//typedef struct {
//	PATCHJOB_TYPE type;
//	BYTE* address;
//	BYTE* bytes;
//	int numBytes;
//	void* pFunction;
//	DWORD64* pReturn;
//	BYTE lastByteCheck;
//	int reapplyCount;
//} PatchJob;

typedef struct {
	GAMEPATCH_TYPE type;
	BYTE* address;
	BYTE* bytes;
	int numBytes;
	void* pFunction;
	DWORD64* pReturn;
} GamePatch;