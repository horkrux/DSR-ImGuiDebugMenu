#pragma once

//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>

// D3d Related Files
#include "ImGui/imgui.h"
#include "imgui_impl_dx11.h"
#include "MinHook/include/MinHook.h"
#include <DXGI.h>
#include <d3d11.h>
#include <TlHelp32.h>
#include "Menu.h"

extern int g_dbgMenuWidth;
extern int g_dbgMenuHeight;
extern int g_dbgMenuPosX;
extern int g_dbgMenuPosY;