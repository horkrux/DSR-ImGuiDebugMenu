#include "stdafx.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace ImGui;

static LogOutputConsole console;
static bool first = true;

HANDLE hProcess;

static void ShowDbgOutputLog(bool* p_open)
{
	console.Draw("Debug Log Console", p_open);
}

//https://stackoverflow.com/questions/24686846/get-current-time-in-milliseconds-or-hhmmssmmm-format
//answer by Galik
std::string time_in_HH_MM_SS_MMM()
{
	using namespace std::chrono;

	// get current time
	auto now = system_clock::now();

	// get number of milliseconds for the current second
	// (remainder after division into seconds)
	auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

	// convert to std::time_t in order to convert to std::tm (broken time)
	auto timer = system_clock::to_time_t(now);

	// convert to broken time
	std::tm bt = *std::localtime(&timer);

	std::ostringstream oss;

	oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
	oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

	return oss.str();
}

VOID PrintDbgLog(wchar_t* format, char* args, byte* chrPtr)
{
	wchar_t buffer[256];
	char nameBuffer[64];
	char newbuf[1024];
	char newbuf2[1024];
	vswprintf(buffer, 256, format, args);

	WideCharToMultiByte(CP_UTF8, 0, buffer, -1, newbuf, 1024, NULL, NULL);

	int stringLen = *(int*)(chrPtr + 0x510);
	byte* stringPos = chrPtr + 0x4F8;

	if (stringLen >= 8)
		stringPos = (byte*)*(uint64_t*)stringPos;

	WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)stringPos, -1, nameBuffer, 64, NULL, NULL);

	sprintf(newbuf2, "%s: [ESD:%s] %s", time_in_HH_MM_SS_MMM(), nameBuffer, newbuf);

	console.AddLog(newbuf2);
}

DWORD64 fPrintDbgLog = (DWORD64)&PrintDbgLog;

void PrintText(DWORD64 ai, char* str)
{
	long long sthPtr = 0;

	ReadProcessMemory(hProcess, (LPVOID)(ai + 8), &sthPtr, 8, NULL);

	if (sthPtr)
	{
		ReadProcessMemory(hProcess, (LPVOID)sthPtr, &sthPtr, 8, NULL);

		if (sthPtr)
		{
			long long chrCtrl = 0;

			ReadProcessMemory(hProcess, (LPVOID)(sthPtr + 0x10), &chrCtrl, 8, NULL);

			if (chrCtrl)
			{
				uint64_t chrIns = 0;

				if (chrCtrl)
				{
					ReadProcessMemory(hProcess, (LPVOID)(chrCtrl + 0x10), &chrIns, 8, NULL);

					int count = 0;
					char read_char;
					char chrName[32];
					char strNew[320];
					int stringLen = 0;
					uint64_t stringPos = chrIns + 0x4F8;

					ReadProcessMemory(hProcess, (LPVOID)(chrIns + 0x510), &stringLen, 4, NULL);

					if (stringLen >= 8)
						ReadProcessMemory(hProcess, (LPVOID)(chrIns + 0x4F8), &stringPos, 8, NULL);

					do
					{
						ReadProcessMemory(hProcess, (LPVOID)(stringPos + count * 2), &read_char, 1, NULL);
						chrName[count] = read_char;
						count++;
					} while (read_char);

					sprintf(strNew, "%s: [AI:%s] %s", time_in_HH_MM_SS_MMM(), chrName, str);
					//sprintf(strNew, "(%s) %s", chrName, str);

					console.AddLog(strNew);
				}
			}
		}
	}
}

float test = 1;
long long dispgroup_address = 0;
long long worldChrManDbgPtrAddress = 0x141D151F8;
long long worldAiManPtrAddress = 0x141D1F878;
long long damageManPtrAddress = 0x141D173C0;
long long dispgroup_address_base = 0x141D11D38;
long long worldChrManPtrAddress = 0x141D151B0;
long long msbResPtrAddress = 0x141D1AE98;
long long gameManPtrAddress = 0x141D10E18;

//DWORD64 bGetCameraObj = 0;
//DWORD64 bSetCameraObj = 0;
//DWORD64 bGetCameraObjAlt = 0;

//char part_strings[17][5000][100];

BYTE antiTamperPatch[2] = { 0x90, 0x90 };
//BYTE boot_patch[4] = { 0x55, 0x67, 0xFE, 0xFF };
//BYTE dbg_patch[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };


bool Hook(void* toHook, void* ourFunc, int len)
{
	if (len < 5)
	{
		return false;
	}

	DWORD curProtec;
	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtec);

	memset(toHook, 0x90, len);

	DWORD64 relativeAddress = ((DWORD64)ourFunc - (DWORD64)toHook) - 5;

	*(BYTE*)toHook = 0xE9;
	*(DWORD64*)((DWORD64)toHook + 1) = relativeAddress;

	DWORD temp;
	VirtualProtect(toHook, len, curProtec, &temp);

	return true;
}

void Menu::ApplyPatches()
{
	DWORD oldProtect;
	void* ptr = &PrintText;
	//MH_CreateHook((LPVOID)hookAddress, (LPVOID)PrintText, 0);
	//MH_EnableHook((LPVOID)hookAddress);
	VirtualProtect((LPVOID)0x141ACCC18, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x141ACCC18, &ptr, 8);
	VirtualProtect((LPVOID)0x141ACCC18, 8, oldProtect, &oldProtect);

	//antitamper 1
	VirtualProtect((LPVOID)0x142CF7ACE, 2, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x142CF7ACE, antiTamperPatch, 2);
	VirtualProtect((LPVOID)0x142CF7ACE, 2, oldProtect, &oldProtect);

	//antitamper2
	VirtualProtect((LPVOID)0x14270A5D8, 2, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)0x14270A5D8, antiTamperPatch, 2);
	VirtualProtect((LPVOID)0x14270A5D8, 2, oldProtect, &oldProtect);

	//esd output log
	MH_CreateHook((LPVOID)0x1403913ED, (LPVOID)tEsdDbgLogOutput, 0);
	MH_EnableHook((LPVOID)0x1403913ED);
}

void Menu::ReapplyPatches()
{
	//esd output log
	byte code = 0;
	ReadProcessMemory(hProcess, (LPVOID)0x1403913ED, &code, 1, NULL);
	
	if (code == 0x83)
	{
		MH_CreateHook((LPVOID)0x1403913ED, (LPVOID)tEsdDbgLogOutput, 0);
		MH_EnableHook((LPVOID)0x1403913ED);
	}

	
}

typedef __int64(__thiscall* _genericThisCall1)(uint64_t* this_ptr);

typedef __int64(__fastcall* _SwitchControlPlayer)(__int64 some_ptr, __int64 enemy_ptr);
_SwitchControlPlayer SwitchControlPlayer = (_SwitchControlPlayer)0x140374D50;

typedef char(__thiscall* _dbgMenuPressEnterButtonListener)(__int64 this_ptr, int idx);
_dbgMenuPressEnterButtonListener dbgMenuPressEnterButtonListener = (_dbgMenuPressEnterButtonListener)0x1403362D0;



DWORD GetProcId(const wchar_t* procname) 
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

Menu::Menu()
{
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcId(L"DarkSoulsRemastered.exe"));
}

Menu::~Menu()
{
	CloseHandle(hProcess);
}



void Menu::Render()
{
	ImGui_ImplDX11_NewFrame();

	static bool no_titlebar = false;
	static bool no_border = true;
	static bool no_resize = false;
	static bool auto_resize = false;
	static bool no_move = false;
	static bool no_scrollbar = false;
	static bool no_collapse = false;
	static bool no_menu = true;
	static bool start_pos_set = false;

	static bool show_console = false;
	show_console = g_isOpenConsole;

	if (g_isOpenConsole) {
		//g_isOpenConsole = false;
		ShowDbgOutputLog((bool*)&g_isOpenConsole);
	}

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.61f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	
	ImGuiWindowFlags	window_flags = 0;
	if (no_titlebar)	window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_resize)		window_flags |= ImGuiWindowFlags_NoResize;
	if (auto_resize)	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	if (no_move)		window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar)	window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)	window_flags |= ImGuiWindowFlags_NoCollapse;
	if (!no_menu)		window_flags |= ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowSize(ImVec2(g_dbgMenuWidth, g_dbgMenuHeight), ImGuiCond_Once);
	if (!start_pos_set) { ImGui::SetNextWindowPos(ImVec2(g_dbgMenuPosX, g_dbgMenuPosY)); start_pos_set = true; }

	ImGui::GetIO().MouseDrawCursor = g_isOpenConsole;

	if (first)
	{
		ApplyPatches();
		first = false;
	}

	//ReapplyPatches();

	if (IsOpen)
	{
		//ImGui::Begin("Discount Debug Menu", &IsOpen, window_flags);

		//ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);
		//ImGui::PushItemWidth(-140);

		//ImGui::Text("Kanjis: \xe2\x96\xa0\xe2\x89\xaasda\xe3\x80\x87\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");

		//if (ImGui::Button("Open Console"))
		//{
		//	show_console = true;
		//}		

		//if (ImGui::CollapsingHeader("[ROOT](6)")) 
		//{
		//	RenderSystemMenu();

		//	if (ImGui::CollapsingHeader("[RESOURCE]"))
		//	{
		//		if (ImGui::TreeNode("[MTD MAN]"))
		//		{
		//			if (ImGui::TreeNode("[OPTION]"))
		//			{
		//				{
		//					const char* items[] = { "DEFAULT", "NORMAL", "GHOST", "HemEnv", "HemEnvLerp", "DbgNormal", "DbgNormalErrCheck(THIS WILL CRASH)", "DbgPointNum" };
		//					static int item_current = 0;
		//					if (ImGui::Combo("ForceChangeShaderMode", &item_current, items, IM_ARRAYSIZE(items)))
		//					{
		//						int temp_val = item_current - 1;
		//						if (temp_val != 5)
		//							WriteProcessMemory(hProcess, (LPVOID)0x141AC60D0, &temp_val, 4, NULL);
		//					}
		//				}

		//				{
		//					const char* items[] = { "DISABLED", "LitColor", "DiffuseColor", "SpecularColor", "EmissiveColor", "Normal", "Roughness", "Subsurface", "Ambient Occlusion" };
		//					static int item_current = 0;
		//					if (ImGui::Combo("Gbuffer debug", &item_current, items, IM_ARRAYSIZE(items)))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D0DD18, &item_current, 4, NULL);
		//					}
		//				}

		//				ImGui::TreePop();
		//			}

		//			ImGui::TreePop();
		//		}
		//	}

		//	if (ImGui::CollapsingHeader("[GAME]"))
		//	{
		//		if (ImGui::TreeNode("[MAP INS]"))
		//		{
		//			if (ImGui::TreeNode("[WORLD MAP MAN]"))
		//			{
		//				if (ImGui::TreeNode("[m10_02_00_00]"))
		//				{
		//					static int dispgroup1;
		//					static int dispgroup2;
		//					static int dispgroup3;
		//					static int dispgroup4;
		//					ReadProcessMemory(hProcess, (LPVOID)dispgroup_address_base, &dispgroup_address, 8, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(dispgroup_address + 0x30), &dispgroup_address, 8, NULL);
		//					dispgroup_address += 0x118; //for m10_02_00_00
		//					ReadProcessMemory(hProcess, (LPVOID)dispgroup_address, &dispgroup1, 4, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(dispgroup_address+4), &dispgroup2, 4, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(dispgroup_address+8), &dispgroup3, 4, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(dispgroup_address+12), &dispgroup4, 4, NULL);
		//					ImGui::Text("DispGroup> %d", dispgroup1);
		//					ImGui::Text("DispGroup> %d", dispgroup2);
		//					ImGui::Text("DispGroup> %d", dispgroup3);
		//					ImGui::Text("DispGroup> %d", dispgroup4);

		//					ImGui::TreePop();
		//				}

		//				ImGui::TreePop();
		//			}

		//			ImGui::TreePop();
		//		}

		//		if (ImGui::TreeNode("[CHR INS]"))
		//		{
		//			if (ImGui::TreeNode("[WORLD CHR MAN]"))
		//			{
		//				static long long worldChrManPtr = 0;
		//				static int num_backread_areas = 0;
		//				static long long worldBlockChrPtr = 0;

		//				static long long msbResPtr = 0;

		//				ReadProcessMemory(hProcess, (LPVOID)worldChrManPtrAddress, &worldChrManPtr, 8, NULL);

		//				//if (!msb_res_ptr) 
		//				//{
		//					
		//				//}

		//				if (worldChrManPtr) 
		//				{
		//					long long msbResCapPtr = 0;
		//					int num_maps = 0;
		//					int num_enemies = 0;

		//					ReadProcessMemory(hProcess, (LPVOID)(worldChrManPtr + 0x30), &worldBlockChrPtr, 8, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(worldChrManPtr + 0x28), &num_maps, 4, NULL);

		//					for (int i = 0; i < num_maps; i++)
		//					{

		//						/*long long msb_parts_offset = 0;

		//						wchar_t map_name[13];

		//						long long temp_map_name_offset = 0;

		//						ReadProcessMemory(hProcess, (LPVOID)(msbResPtr + 0xa0 + i * 0x10), &msbResCapPtr, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(msbResCapPtr + 8), &temp_map_name_offset, 8, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)temp_map_name_offset, map_name, 26, NULL);

		//						char map_name_8[13];

		//						for (int j = 0; j < 13; j++) {
		//							map_name_8[j] = map_name[j];
		//						}*/
		//						long long worldBlockInfo = 0;
		//						unsigned int mapUuid = 0;
		//						ReadProcessMemory(hProcess, (LPVOID)(worldBlockChrPtr + 8 + 0xE8 * i), &worldBlockInfo, 8, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(worldBlockChrPtr + 0x48 + 0xE8 * i), &num_enemies, 4, NULL);

		//						if (!num_enemies)
		//							continue;

		//						ReadProcessMemory(hProcess, (LPVOID)(worldBlockInfo + 8), &mapUuid, 4, NULL);

		//						char map_name[32];
		//						sprintf(map_name, "[m%02d_%02d_%02d_%02d](%d)", mapUuid >> 24, mapUuid >> 16 & 0xFF, mapUuid >> 8 & 0xFF, mapUuid & 0xFF, num_enemies + 1);

		//						if (ImGui::TreeNode(map_name)) {

		//							long long chrPtrList = 0;
		//							long long chrPtr = 0;

		//							ReadProcessMemory(hProcess, (LPVOID)(worldBlockChrPtr + 0x50 + 0xE8 * i), &chrPtrList, 8, NULL);

		//							for (int j = 0; j < num_enemies; j++)
		//							{
		//								ReadProcessMemory(hProcess, (LPVOID)(chrPtrList + 0x38 * j), &chrPtr, 8, NULL);

		//								RenderWorldChrManChrEntry(chrPtr, false, j);
		//								
		//							}

		//							ImGui::TreePop();
		//						}
		//						
		//					}

		//					long long player_ptr = 0;

		//					ReadProcessMemory(hProcess, (LPVOID)(worldChrManPtr + 0x68), &player_ptr, 8, NULL);

		//					if (player_ptr)
		//					{
		//						RenderWorldChrManChrEntry(player_ptr, true, 0);
		//					}

		//				}
		//				
		//				ImGui::TreePop();
		//			}

		//			if (ImGui::TreeNode("[CHR DBG]"))
		//			{
		//				static long long worldChrManDbg = 0;

		//				//if (!worldChrManDbg)
		//				//{
		//					ReadProcessMemory(hProcess, (LPVOID)worldChrManDbgPtrAddress, &worldChrManDbg, 8, NULL);
		//				//}

		//				if (worldChrManDbg)
		//				{
		//					bool all_draw_hit = 0;
		//					bool player_no_dead = 0;
		//					bool player_exterminate = 0;
		//					bool all_no_dead = 0;
		//					bool all_no_damage = 0;
		//					bool all_no_hit = 0;
		//					bool all_no_attack = 0;
		//					bool all_no_move = 0;
		//					bool all_no_update_ai = 0;
		//					bool all_no_stamina_consume = 0;
		//					bool all_no_mp_consume = 0;
		//					bool all_no_arrow_consume = 0;
		//					bool all_no_magicqty_consume = 0;
		//					bool player_hide = 0;
		//					bool player_silence = 0;
		//					bool new_knockback_mode = 0;

		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151C9, &player_no_dead, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151CA, &player_exterminate, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151D1, &all_no_dead, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151D2, &all_no_damage, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151D3, &all_no_hit, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151D4, &all_no_attack, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151D5, &all_no_move, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151D6, &all_no_update_ai, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151CB, &all_no_stamina_consume, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151CC, &all_no_mp_consume, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151CD, &all_no_arrow_consume, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151CE, &all_no_magicqty_consume, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151CF, &player_hide, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)0x141D151D0, &player_silence, 1, NULL);


		//					ReadProcessMemory(hProcess, (LPCVOID)(worldChrManDbg + 0x39), &all_draw_hit, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPCVOID)(worldChrManDbg + 0xDC), &new_knockback_mode, 1, NULL);

		//					if (ImGui::Checkbox("Player No Dead", &player_no_dead))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151C9, &player_no_dead, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("Player Exterminate", &player_exterminate))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151CA, &player_exterminate, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No Dead", &all_no_dead))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151D1, &all_no_dead, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No Damage", &all_no_damage))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151D2, &all_no_damage, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No Hit", &all_no_hit))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151D3, &all_no_hit, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No Attack", &all_no_attack))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151D4, &all_no_attack, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No Move", &all_no_move))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151D5, &all_no_move, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No Update Ai", &all_no_update_ai))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151D6, &all_no_update_ai, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No Stamina Consume", &all_no_stamina_consume))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151CB, &all_no_stamina_consume, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No MP Consume", &all_no_mp_consume))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151CC, &all_no_mp_consume, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No Arrow Consume", &all_no_arrow_consume))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151CD, &all_no_arrow_consume, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All No MagicQty Consume", &all_no_magicqty_consume))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151CE, &all_no_magicqty_consume, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("Player Hide", &player_hide))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151CF, &player_hide, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("Player Silence", &player_silence))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)0x141D151D0, &player_silence, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("New KnockBackMode", &new_knockback_mode))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(worldChrManDbg + 0xDC), &new_knockback_mode, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("All Draw Hit", &all_draw_hit))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(worldChrManDbg + 0x39), &all_draw_hit, 1, NULL);
		//					}
		//				}

		//				ImGui::TreePop();
		//			}

		//			ImGui::TreePop();
		//		}

		//		uint64_t gameManPtr = 0;

		//		if (ImGui::TreeNode("[GAME MAN OPTION]"))
		//		{
		//			ReadProcessMemory(hProcess, (LPVOID)gameManPtrAddress, &gameManPtr, 8, NULL);

		//			if (gameManPtr)
		//			{	
		//				bool hitIsDispMapModel = false;
		//				bool hitIsDispLoHit = false;
		//				bool hitIsDispHiHit = false;
		//				bool isDisableAllAreaEne = false;
		//				bool isDisableAllAreaEvent = false;
		//				bool isDisableAllAreaMap = false;
		//				bool isDisableAllAreaObj = false;
		//				bool isEnableAllAreaObj = false;
		//				bool isEnableAllAreaObjBreak = false;
		//				bool isDisableAllAreaHiHit = false;
		//				bool isEnableAllAreaLoHit = false;
		//				bool isDisableAllAreaSfx = false;
		//				bool isDisableAllAreaSound = false;
		//				bool isObjBreakRecordMode = false;
		//				bool isAutoMapWarpMode = false;
		//				bool isChrNpcWanderTest = false;
		//				bool isDbgChrAllDead = false;
		//				bool bRequestToEnding = false;
		//				bool isSaveMode = false;
		//				bool isFpsDisconnection = false;
		//				bool isTitleStart = false;
		//				bool isOnlineMode = false;
		//				bool isIgnoreLeaveMessages = false;
		//				bool isMatchingKeywordClient = false;
		//				bool isNoInput = false;

		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD31), &hitIsDispMapModel, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD32), &hitIsDispLoHit, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD33), &hitIsDispHiHit, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3F), &isDisableAllAreaEne, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD40), &isDisableAllAreaEvent, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD41), &isDisableAllAreaMap, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD42), &isDisableAllAreaObj, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD43), &isEnableAllAreaObj, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD44), &isEnableAllAreaObjBreak, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD45), &isDisableAllAreaHiHit, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD46), &isEnableAllAreaLoHit, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD47), &isDisableAllAreaSfx, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD48), &isDisableAllAreaSound, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD49), &isObjBreakRecordMode, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD4A), &isAutoMapWarpMode, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD4B), &isChrNpcWanderTest, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD4C), &isDbgChrAllDead, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB48), &bRequestToEnding, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB70), &isSaveMode, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB7C), &isFpsDisconnection, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB7E), &isTitleStart, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB7D), &isOnlineMode, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB93), &isIgnoreLeaveMessages, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB91), &isMatchingKeywordClient, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB97), &isNoInput, 1, NULL);

		//				if (ImGui::TreeNode("[HIT Debugging]"))
		//				{
		//					float blinkingInterval = 0.f;

		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD28), &blinkingInterval, 4, NULL);

		//					ImGui::PushItemWidth(200);

		//					if (ImGui::SliderFloat("Blinking Interval [sec]", &blinkingInterval, 0.f, 10.f))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD28), &blinkingInterval, 4, NULL);
		//					}

		//					ImGui::PopItemWidth();

		//					if (ImGui::Checkbox("<IsDispMapModel", &hitIsDispMapModel))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD31), &hitIsDispMapModel, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<IsDispLoHit", &hitIsDispLoHit))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD32), &hitIsDispLoHit, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<IsDispHiHit", &hitIsDispHiHit))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD33), &hitIsDispHiHit, 1, NULL);
		//					}

		//					ImGui::TreePop();
		//				}


		//				if (ImGui::Checkbox("<IsDisableAllAreaEne", &isDisableAllAreaEne))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3F), &isDisableAllAreaEne, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsDisableAllAreaEvent", &isDisableAllAreaEvent))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD40), &isDisableAllAreaEvent, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsDisableAllAreaMap", &isDisableAllAreaMap))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD41), &isDisableAllAreaMap, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsDisableAllAreaObj", &isDisableAllAreaObj))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD42), &isDisableAllAreaObj, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsEnableAllAreaObj", &isEnableAllAreaObj))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD43), &isEnableAllAreaObj, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsEnableAllAreaObjBreak", &isEnableAllAreaObjBreak))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD44), &isEnableAllAreaObjBreak, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsDisableAllAreaHiHit", &isDisableAllAreaHiHit))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD45), &isDisableAllAreaHiHit, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsEnableAllAreaLoHit", &isEnableAllAreaLoHit))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD46), &isEnableAllAreaLoHit, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsDisableAllAreaSfx", &isDisableAllAreaSfx))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD47), &isDisableAllAreaSfx, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsDisableAllAreaSound", &isDisableAllAreaSound))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD48), &isDisableAllAreaSound, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsObjBreakRecordMode", &isObjBreakRecordMode))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD49), &isObjBreakRecordMode, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsAutoMapWarpMode", &isAutoMapWarpMode))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD4A), &isAutoMapWarpMode, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsChrNpcWanderTest", &isChrNpcWanderTest))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD4B), &isChrNpcWanderTest, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsDbgChrAllDead", &isDbgChrAllDead))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD4C), &isDbgChrAllDead, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<bRequestToEnding", &bRequestToEnding))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB48), &bRequestToEnding, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsSaveMode", &isSaveMode))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB70), &isSaveMode, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsFpsDisconnection", &isFpsDisconnection))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB7C), &isFpsDisconnection, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsTitleStart", &isTitleStart))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB7E), &isTitleStart, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsOnlineMode", &isOnlineMode))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB7D), &isOnlineMode, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsIgnoreLeaveMessages", &isIgnoreLeaveMessages))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB93), &isIgnoreLeaveMessages, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsMatchingKeywordClient", &isMatchingKeywordClient))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB91), &isMatchingKeywordClient, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("<IsNoInput", &isNoInput))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB97), &isNoInput, 1, NULL);
		//				}

		//				if (ImGui::TreeNode("[CHECKSUM TAMPERING]"))
		//				{
		//					bool updateEnabled = false;
		//					bool tamperingFlagLevel = false;
		//					bool tamperingFlagStatus = false;
		//					bool tamperingFlagArcheType = false;
		//					bool tamperingFlagCovenant = false;
		//					bool tamperingFlagRegion = false;
		//					bool tamperingFlagSoulAmount = false;
		//					bool tamperingFlagTotalSoulAmount = false;
		//					bool tamperingFlagEquippedArrowBoltId = false;
		//					bool tamperingFlagEquippedArmorId = false;
		//					bool tamperingFlagEquippedItemId = false;
		//					bool tamperingFlagEquippedMagicId = false;

		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB95), &updateEnabled, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD34), &tamperingFlagLevel, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD35), &tamperingFlagStatus, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD36), &tamperingFlagArcheType, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD37), &tamperingFlagCovenant, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD38), &tamperingFlagRegion, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD39), &tamperingFlagSoulAmount, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3A), &tamperingFlagTotalSoulAmount, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3B), &tamperingFlagEquippedArrowBoltId, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3C), &tamperingFlagEquippedArmorId, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3D), &tamperingFlagEquippedItemId, 1, NULL);
		//					ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3E), &tamperingFlagEquippedMagicId, 1, NULL);

		//					if (ImGui::Checkbox("<Update Enabled", &updateEnabled))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xB95), &updateEnabled, 1, NULL);
		//					}

		//					ImGui::Text("--- Tampering flags ---");

		//					if (ImGui::Checkbox("<level", &tamperingFlagLevel))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD34), &tamperingFlagLevel, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<status", &tamperingFlagStatus))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD35), &tamperingFlagStatus, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<arche_type", &tamperingFlagArcheType))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD36), &tamperingFlagArcheType, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<covenant", &tamperingFlagCovenant))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD37), &tamperingFlagCovenant, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<region", &tamperingFlagRegion))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD38), &tamperingFlagRegion, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<soul_amount", &tamperingFlagSoulAmount))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD39), &tamperingFlagSoulAmount, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<total_soul_amount", &tamperingFlagTotalSoulAmount))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3A), &tamperingFlagTotalSoulAmount, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<equipped_arrow_bolt_id", &tamperingFlagEquippedArrowBoltId))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3B), &tamperingFlagEquippedArrowBoltId, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<equipped_armor_id", &tamperingFlagEquippedArmorId))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3C), &tamperingFlagEquippedArmorId, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<equipped_item_id", &tamperingFlagEquippedItemId))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3D), &tamperingFlagEquippedItemId, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("<equipped_magic_id", &tamperingFlagEquippedMagicId))
		//					{
		//						WriteProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xD3E), &tamperingFlagEquippedMagicId, 1, NULL);
		//					}

		//					if (ImGui::TreeNode("[CHECKSUM VALUES]"))
		//					{
		//						//this normally receives a value to decide whether to even display this shit at all

		//						uint64_t playerValues = 0;
		//						uint16_t equipmentValues1 = 0;
		//						uint8_t equipmentValues2 = 0;

		//						uint32_t checksumValueLevelCurrVal = 0;
		//						uint32_t checksumValueLevelSaveVal = 0;
		//						uint32_t checksumValueStatusCurrVal = 0;
		//						uint32_t checksumValueStatusSaveVal = 0;
		//						uint32_t checksumValueArcheTypeCurrVal = 0;
		//						uint32_t checksumValueArcheTypeSaveVal = 0;
		//						uint32_t checksumValueCovenantCurrVal = 0;
		//						uint32_t checksumValueCovenantSaveVal = 0;
		//						uint32_t checksumValueRegionCurrVal = 0;
		//						uint32_t checksumValueRegionSaveVal = 0;
		//						uint32_t checksumValueSoulAmountCurrVal = 0;
		//						uint32_t checksumValueSoulAmountSaveVal = 0;
		//						uint32_t checksumValueTotalSoulAmountCurrVal = 0;
		//						uint32_t checksumValueTotalSoulAmountSaveVal = 0;
		//						uint32_t checksumValueEquippedArrowBoltIdCurrVal = 0;
		//						uint32_t checksumValueEquippedArrowBoltIdSaveVal = 0;
		//						uint32_t checksumValueEquippedArmorIdCurrVal = 0;
		//						uint32_t checksumValueEquippedArmorIdSaveVal = 0;
		//						uint32_t checksumValueEquippedItemIdCurrVal = 0;
		//						uint32_t checksumValueEquippedItemIdSaveVal = 0;
		//						uint32_t checksumValueEquippedMagicIdCurrVal = 0;
		//						uint32_t checksumValueEquippedMagicIdSaveVal = 0;

		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xCB4), &playerValues, 8, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xCBC), &equipmentValues1, 2, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xCBE), &equipmentValues2, 1, NULL);

		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC88), &checksumValueLevelCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC5C), &checksumValueLevelSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC8C), &checksumValueStatusCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC60), &checksumValueStatusSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC90), &checksumValueArcheTypeCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC64), &checksumValueArcheTypeSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC94), &checksumValueCovenantCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC68), &checksumValueCovenantSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC98), &checksumValueRegionCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC6C), &checksumValueRegionSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC9C), &checksumValueSoulAmountCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC70), &checksumValueSoulAmountSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xCA0), &checksumValueTotalSoulAmountCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC74), &checksumValueTotalSoulAmountSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xCA4), &checksumValueEquippedArrowBoltIdCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC78), &checksumValueEquippedArrowBoltIdSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xCA8), &checksumValueEquippedArmorIdCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC7C), &checksumValueEquippedArmorIdSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xCAC), &checksumValueEquippedItemIdCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC80), &checksumValueEquippedItemIdSaveVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xCB0), &checksumValueEquippedMagicIdCurrVal, 4, NULL);
		//						ReadProcessMemory(hProcess, (LPVOID)(gameManPtr + 0xC84), &checksumValueEquippedMagicIdSaveVal, 4, NULL);

		//						ImGui::Text("level=%d currval=%u saveval=%u", playerValues & 0xFF, checksumValueLevelCurrVal, checksumValueLevelSaveVal);
		//						ImGui::Text("status=%d currval=%u saveval=%u", playerValues >> 8 & 0xFF, checksumValueStatusCurrVal, checksumValueStatusSaveVal);
		//						ImGui::Text("arche_type=%d currval=%u saveval=%u", playerValues >> 16 & 0xFF, checksumValueArcheTypeCurrVal, checksumValueArcheTypeSaveVal);
		//						ImGui::Text("covenant=%d currval=%u saveval=%u", playerValues >> 24 & 0xFF, checksumValueCovenantCurrVal, checksumValueCovenantSaveVal);
		//						ImGui::Text("region=%d currval=%u saveval=%u", playerValues >> 32 & 0xFF, checksumValueRegionCurrVal, checksumValueRegionSaveVal);
		//						ImGui::Text("soul_amount=%d currval=%u saveval=%u", playerValues >> 40 & 0xFF, checksumValueSoulAmountCurrVal, checksumValueSoulAmountSaveVal);
		//						ImGui::Text("total_soul_amount=%d currval=%u saveval=%u", playerValues >> 48 & 0xFF, checksumValueTotalSoulAmountCurrVal, checksumValueTotalSoulAmountSaveVal);
		//						ImGui::Text("equipped_arrow_bolt_id=%d currval=%u saveval=%u", playerValues >> 56 & 0xFFFFFFFF, checksumValueEquippedArrowBoltIdCurrVal, checksumValueEquippedArrowBoltIdSaveVal);
		//						ImGui::Text("equipped_armor_id=%d currval=%u saveval=%u", equipmentValues1 & 0xFF, checksumValueEquippedArmorIdCurrVal, checksumValueEquippedArmorIdSaveVal);
		//						ImGui::Text("equipped_item_id=%d currval=%u saveval=%u", equipmentValues1 >> 8 & 0xFF, checksumValueEquippedItemIdCurrVal, checksumValueEquippedItemIdSaveVal);
		//						ImGui::Text("equipped_magic_id=%d currval=%u saveval=%u", equipmentValues2, checksumValueEquippedMagicIdCurrVal, checksumValueEquippedMagicIdSaveVal);

		//						ImGui::TreePop();
		//					}

		//					ImGui::TreePop();
		//				}
		//				
		//			}

		//			ImGui::TreePop();
		//		}

		//		if (ImGui::TreeNode("[WorldAiMan]"))
		//		{
		//			static long long worldAiMan = 0;

		//			//if (!worldAiMan)
		//			//{
		//				ReadProcessMemory(hProcess, (LPVOID)worldAiManPtrAddress, &worldAiMan, 8, NULL);
		//			//}

		//			if (worldAiMan)
		//			{
		//				if (ImGui::TreeNode("[OnChr]"))
		//				{
		//					BYTE onChrFlags = 0;

		//					ReadProcessMemory(hProcess, (LPVOID)(worldAiMan + 0x1890), &onChrFlags, 1, NULL);

		//					bool draw_battle_state = onChrFlags & 1;
		//					bool draw_entity_id = onChrFlags >> 2 & 1;
		//					bool draw_ladder_flag = onChrFlags >> 4 & 1;
		//					bool draw_goal = onChrFlags >> 1 & 1;


		//					if (ImGui::Checkbox("Draw Goal On Chr", &draw_goal))
		//					{
		//						if (draw_goal) {
		//							onChrFlags |= 2;
		//						}
		//						else {
		//							onChrFlags &= 0xFD;
		//						}

		//						WriteProcessMemory(hProcess, (LPVOID)(worldAiMan + 0x1890), &onChrFlags, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("Draw Battle State On Chr", &draw_battle_state))
		//					{
		//						if (draw_battle_state) {
		//							onChrFlags |= 1;
		//						}
		//						else {
		//							onChrFlags &= 0xFE;
		//						}

		//						WriteProcessMemory(hProcess, (LPVOID)(worldAiMan + 0x1890), &onChrFlags, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("Draw Entity ID On Chr", &draw_entity_id))
		//					{
		//						if (draw_entity_id) {
		//							onChrFlags |= 4;
		//						}
		//						else {
		//							onChrFlags &= 0xFB;
		//						}

		//						WriteProcessMemory(hProcess, (LPVOID)(worldAiMan + 0x1890), &onChrFlags, 1, NULL);
		//					}

		//					if (ImGui::Checkbox("Draw Ladder Flag On Chr", &draw_ladder_flag))
		//					{
		//						if (draw_ladder_flag) {
		//							onChrFlags |= 16;
		//						}
		//						else {
		//							onChrFlags &= 0xEF;
		//						}

		//						WriteProcessMemory(hProcess, (LPVOID)(worldAiMan + 0x1890), &onChrFlags, 1, NULL);
		//					}

		//					ImGui::TreePop();
		//				}
		//			}

		//			ImGui::TreePop();
		//		}

		//		if (ImGui::TreeNode("[DAMAGE MAN]"))
		//		{
		//			static long long damageMan = 0;

		//			ReadProcessMemory(hProcess, (LPVOID)damageManPtrAddress, &damageMan, 8, NULL);

		//			if (damageMan)
		//			{
		//				bool debug_ball_display = 0;
		//				bool debug_info_display = 0;
		//				bool damage_arising_weapon_dami = 0;
		//				bool damage_refer_atk_param = 0;
		//				float distance_to_spark = 0;
		//				float slope_of_lohits = 0;

		//				ReadProcessMemory(hProcess, (LPVOID)0x141AC8910, &slope_of_lohits, 4, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(damageMan + 0x1C), &distance_to_spark, 4, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(damageMan + 0x30), &debug_ball_display, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(damageMan + 0x31), &debug_info_display, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(damageMan + 0x32), &damage_arising_weapon_dami, 1, NULL);
		//				ReadProcessMemory(hProcess, (LPVOID)(damageMan + 0x33), &damage_refer_atk_param, 1, NULL);

		//				


		//				if (ImGui::Checkbox("Debug ball display", &debug_ball_display))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(damageMan + 0x30), &debug_ball_display, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("Debug information display", &debug_info_display))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(damageMan + 0x31), &debug_info_display, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("Damage arising from weapons damipoly", &damage_arising_weapon_dami))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(damageMan + 0x32), &damage_arising_weapon_dami, 1, NULL);
		//				}

		//				if (ImGui::Checkbox("Damage to occur with reference attack parameters", &damage_refer_atk_param))
		//				{
		//					WriteProcessMemory(hProcess, (LPVOID)(damageMan + 0x33), &damage_refer_atk_param, 1, NULL);
		//				}

		//				if (ImGui::InputFloat("Distance to spark", &distance_to_spark, 0.01f, 0.1f))
		//				{
		//					if (distance_to_spark < 0.0f)
		//					{
		//						distance_to_spark = 1.0f;
		//					}
		//					else if (distance_to_spark > 100.0f)
		//					{
		//						distance_to_spark = 0.0f;
		//					}

		//					WriteProcessMemory(hProcess, (LPVOID)(damageMan + 0x1C), &distance_to_spark, 4, NULL);
		//				}

		//				if (ImGui::InputFloat("Slope of low hits assumed on the floor[angle 0 - 180]", &slope_of_lohits, 0.01f, 0.1f))
		//				{
		//					if (slope_of_lohits < 0.0f)
		//					{
		//						slope_of_lohits = 1.0f;
		//					}
		//					else if (slope_of_lohits > 180.0f)
		//					{
		//						slope_of_lohits = 0.0f;
		//					}

		//					WriteProcessMemory(hProcess, (LPVOID)0x141AC8910, &slope_of_lohits, 4, NULL);
		//				}
		//			}

		//			

		//			ImGui::TreePop();
		//		}
		//	}
		//}
		//

		//ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

//void Menu::RenderWorldChrMan()
//{
//
//}
//
//void Menu::BuildPartNamesList()
//{
//	long long msbResPtr = 0;
//
//	ReadProcessMemory(hProcess, (LPVOID)msbResPtrAddress, &msbResPtr, 8, NULL);
//
//
//
//
//}
//
//void Menu::RenderWorldChrManChrEntry(uint64_t chrPtr, bool isPlayer, int index)
//{
//	int flags1 = 0;
//	ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x524), &flags1, 1, NULL);
//
//	int count = 0;
//	char read_char;
//	char chrName[32];
//	char chrNameNew[40];
//
//	if (!isPlayer)
//	{
//		int stringLen = 0;
//		uint64_t stringPos = chrPtr + 0x4F8;
//		ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x510), &stringLen, 4, NULL);
//
//		if (stringLen >= 8)
//		{
//			ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x4F8), &stringPos, 8, NULL);
//		}
//		do
//		{
//			ReadProcessMemory(hProcess, (LPVOID)(stringPos + count * 2), &read_char, 1, NULL);
//			chrName[count] = read_char;
//			count++;
//		} while (read_char);
//
//		sprintf(chrNameNew, "[%s]##%d", chrName, index);
//	}
//	else {
//		strcpy(chrNameNew, "[c0000]");
//	}
//
//	if (ImGui::TreeNode(chrNameNew))
//	{
//		if (ImGui::IsItemHovered()) {
//			flags1 |= 1;
//			WriteProcessMemory(hProcess, (LPVOID)(chrPtr + 0x524), &flags1, 1, NULL);
//		}
//		
//		unsigned int chrHealth = 0;
//		unsigned int chrHealthMax = 0;
//		unsigned int chrStamina = 0;
//		unsigned int chrStaminaMax = 0;
//		unsigned int chrMana = 0;
//		unsigned int chrManaMax = 0;
//		bool chrEnableEsdDbgLog = 0;
//
//		ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x3E8), &chrHealth, 4, NULL);
//		ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x3EC), &chrHealthMax , 4, NULL);
//		ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x3F0), &chrMana, 4, NULL);
//		ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x3F4), &chrManaMax , 4, NULL);
//		ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x3F8), &chrStamina, 4, NULL);
//		ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x3FC), &chrStaminaMax, 4, NULL);
//		ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x550), &chrEnableEsdDbgLog, 1, NULL);
//
//		/*if (ImGui::Checkbox("Print From ESD Log", &chrEnableEsdDbgLog))
//		{
//			WriteProcessMemory(hProcess, (LPVOID)(chrPtr + 0x550), &chrEnableEsdDbgLog, 1, NULL);
//		}*/
//
//		ImGui::Text("HP : [%d / %d]", chrHealth, chrHealthMax);
//		ImGui::Text("MP : [%d / %d] Stamina : [%d / %d]", chrMana, chrManaMax, chrStamina, chrStaminaMax);
//
//		if (ImGui::Button("Switch Control Player"))
//		{
//			dbgMenuPressEnterButtonListener(chrPtr, 0);
//		}
//
//		if (ImGui::Button("Return Control Player"))
//		{
//			dbgMenuPressEnterButtonListener(chrPtr, 40);
//		}
//
//		if (ImGui::Button("Move Position to this pos"))
//		{
//			dbgMenuPressEnterButtonListener(chrPtr, 42);
//		}
//
//		if (ImGui::Button("Reset Position at InitPos"))
//		{
//			dbgMenuPressEnterButtonListener(chrPtr, 41);
//		}
//
//		if (ImGui::TreeNode("Draw"))
//		{
//			BYTE drawFlags2 = 0;
//			int drawPolygonNum = 0;
//			bool drawDmyPolygon = false;
//			bool drawWepDmyPolygon = false;
//			bool drawBloodMarkPos = false;
//			
//			ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x525), &drawFlags2, 1, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)0x141D11F00, &drawPolygonNum, 4, NULL);
//
//			drawDmyPolygon = drawFlags2 >> 4 & 1;
//
//			if (ImGui::Button("Toggle Draw"))
//			{
//				dbgMenuPressEnterButtonListener(chrPtr, 121);
//			}
//
//			if (ImGui::Checkbox("Draw Dummy Polygon", &drawDmyPolygon))
//			{
//				if (drawDmyPolygon) {
//					drawFlags2 |= 0x10;
//				}
//				else {
//					drawFlags2 &= 0xEF;
//				}
//
//				WriteProcessMemory(hProcess, (LPVOID)(chrPtr + 0x525), &drawFlags2, 1, NULL);
//			}
//
//			ImGui::SameLine();
//
//			int temp_draw_polygon_num = drawPolygonNum;
//			//static int test_draw_polygon_num = 1000;
//
//			if (drawPolygonNum == 0) {
//				if (ImGui::InputInt("(ALL)", &drawPolygonNum))
//				{
//					//WriteProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);
//				}
//			}
//			else
//			{
//				if (drawPolygonNum < 0) drawPolygonNum *= -1;
//
//				if (ImGui::InputInt("(ONLY)", &drawPolygonNum))
//				{
//					//WriteProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);
//				}
//			}
//
//			if (drawPolygonNum != temp_draw_polygon_num)
//				WriteProcessMemory(hProcess, (LPVOID)0x141D11F00, &drawPolygonNum, 4, NULL);
//
//			if (isPlayer)
//			{
//				ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x967), &drawWepDmyPolygon, 1, NULL);
//				ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x968), &drawBloodMarkPos, 1, NULL);
//
//				if (ImGui::Checkbox("Draw Weapon Dummy Polygon", &drawWepDmyPolygon))
//				{
//					WriteProcessMemory(hProcess, (LPVOID)(chrPtr + 0x967), &drawWepDmyPolygon, 1, NULL);
//				}
//
//				if (ImGui::Checkbox("Draw BloodMarkPos", &drawBloodMarkPos))
//				{
//					WriteProcessMemory(hProcess, (LPVOID)(chrPtr + 0x968), &drawBloodMarkPos, 1, NULL);
//				}
//			}
//
//			
//
//			ImGui::TreePop();
//		}
//
//		if (ImGui::TreeNode("Havok"))
//		{
//			if (ImGui::Button("Switch Hit ON/OFF"))
//			{
//				dbgMenuPressEnterButtonListener(chrPtr, 1);
//			}
//
//			if (ImGui::Button("Switch Damage Ragdoll"))
//			{
//				dbgMenuPressEnterButtonListener(chrPtr, 3);
//			}
//
//			if (ImGui::Button("Switch Dead Ragdoll"))
//			{
//				dbgMenuPressEnterButtonListener(chrPtr, 4);
//			}
//
//
//			ImGui::TreePop();
//		}
//
//		if (ImGui::TreeNode("Other"))
//		{
//			if (ImGui::Button("Debug Move"))
//			{
//				dbgMenuPressEnterButtonListener(chrPtr, 20);
//			}
//
//			if (ImGui::Button("Forced Death"))
//			{
//				dbgMenuPressEnterButtonListener(chrPtr, 6);
//			}
//
//			if (ImGui::Button("Completely Disabled"))
//			{
//				dbgMenuPressEnterButtonListener(chrPtr, 8);
//			}
//
//			ImGui::TreePop();
//		}
//
//		uint64_t chrCtrl = 0;
//
//		ReadProcessMemory(hProcess, (LPVOID)(chrPtr + 0x68), &chrCtrl, 8, NULL);
//
//		if (chrCtrl)
//		{
//			uint64_t actionCtrl = 0;
//
//			ReadProcessMemory(hProcess, (LPVOID)(chrCtrl + 0x48), &actionCtrl, 8, NULL);
//
//			if (actionCtrl)
//			{
//				if (ImGui::TreeNode("Action"))
//				{
//					bool printEzStateLog = false;
//
//					ReadProcessMemory(hProcess, (LPVOID)(actionCtrl + 0x550), &printEzStateLog, 1, NULL);
//
//					if (ImGui::Checkbox("Print Logs from EzState", &printEzStateLog))
//					{
//						WriteProcessMemory(hProcess, (LPVOID)(actionCtrl + 0x550), &printEzStateLog, 1, NULL);
//					}
//
//					ImGui::TreePop();
//				}
//			}
//		}
//
//		if (ImGui::TreeNode("Event"))
//		{
//
//			//TODO: IDs
//			if (ImGui::Button("Event -> Issue command to EzState"))
//			{
//				dbgMenuPressEnterButtonListener(chrPtr, 5);
//			}
//
//
//			ImGui::TreePop();
//		}
//
//		if (ImGui::Button("Reset QWC SpecialEffect"))
//		{
//			dbgMenuPressEnterButtonListener(chrPtr, 30);
//		}
//
//		ImGui::TreePop();
//
//	}
//	else {
//		if (ImGui::IsItemHovered()) {
//			flags1 |= 1;
//			WriteProcessMemory(hProcess, (LPVOID)(chrPtr + 0x524), &flags1, 1, NULL);
//		}
//	}
//}
//
//void Menu::RenderSystemMenu()
//{
//	if (ImGui::CollapsingHeader("[SYSTEM]"))
//	{
//		if (ImGui::TreeNode("[MEM MAN](14)"))
//		{
//			uint64_t* memPtrAddress = (uint64_t*)0x141C04F20;
//			uint64_t* memPtr = (uint64_t*)*memPtrAddress;
//
//			uint64_t* vtableMainMem = (uint64_t*)*(memPtr);
//			uint64_t freeMem = ((_genericThisCall1) (vtableMainMem[5]))(memPtr);
//			uint64_t totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			uint64_t max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			uint64_t num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			int id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("MAIN> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem , max >> 10, num, id);
//
//			memPtr = (uint64_t*)0x141AC3858;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("LOCAL> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141C04F40;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("HAVOK> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141C04F30;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("INGAME> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141C04F90;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("CORERES> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141C04F38;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("HGSYS> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141C04F48;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("MO> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141C04F70;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("FFX> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141C04F78;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("MENU> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141C04F88;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("LUA> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141C04FA0;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("DEBUG> FREE:%u/%u[%0.1f%%] MAX:%u NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			memPtrAddress = (uint64_t*)0x141D92E68;
//			memPtr = (uint64_t*)*memPtrAddress;
//
//			vtableMainMem = (uint64_t*)*(memPtr);
//			freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//			totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//			max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//			num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//			id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//			ImGui::Text("DL_RUNTIME> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//			if (ImGui::TreeNode("[Other](6)"))
//			{
//				memPtrAddress = (uint64_t*)0x141C04F98;
//				memPtr = (uint64_t*)*memPtrAddress;
//
//				vtableMainMem = (uint64_t*)*(memPtr);
//				freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//				totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//				max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//				num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//				id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//				ImGui::Text("TEMP> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//				memPtrAddress = (uint64_t*)0x141D95FE8;
//				memPtr = (uint64_t*)*memPtrAddress;
//
//				vtableMainMem = (uint64_t*)*(memPtr);
//				freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//				totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//				max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//				num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//				id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//				ImGui::Text("DL_SYSTEM> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//				memPtrAddress = (uint64_t*)0x141C04F80;
//				memPtr = (uint64_t*)*memPtrAddress;
//
//				vtableMainMem = (uint64_t*)*(memPtr);
//				freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//				totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//				max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//				num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//				id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//				ImGui::Text("FRPGNET> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//				memPtrAddress = (uint64_t*)*(uint64_t*)0x141DA12D8;
//				memPtr = (uint64_t*)*(memPtrAddress + 3);
//				//memPtr = (uint64_t*)*memPtrAddress;
//
//				vtableMainMem = (uint64_t*)*(memPtr);
//				freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//				totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//				max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//				num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//				id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//				ImGui::Text("MO_SYSTEM> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//				memPtrAddress = (uint64_t*)*(uint64_t*)0x141DA12D8;
//				memPtr = (uint64_t*)*(memPtrAddress + 1);
//				//memPtr = (uint64_t*)*memPtrAddress;
//
//				vtableMainMem = (uint64_t*)*(memPtr);
//				freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//				totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//				max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//				num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//				id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//				ImGui::Text("MO_WAVE> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//
//				memPtrAddress = (uint64_t*)*(uint64_t*)0x141DA12D8;
//				memPtr = (uint64_t*)*(memPtrAddress + 2);
//				//memPtr = (uint64_t*)*memPtrAddress;
//
//				vtableMainMem = (uint64_t*)*(memPtr);
//				freeMem = ((_genericThisCall1)(vtableMainMem[5]))(memPtr);
//				totalMem = ((_genericThisCall1)(vtableMainMem[4]))(memPtr);
//				max = ((_genericThisCall1)(vtableMainMem[6]))(memPtr);
//				num = ((_genericThisCall1)(vtableMainMem[7]))(memPtr);
//				id = ((_genericThisCall1)(vtableMainMem[1]))(memPtr);
//
//				ImGui::Text("MO_SOUND> FREE:%d/%d[%0.1f%%] MAX:%d NUM:%d ID:%d", freeMem >> 10, totalMem >> 10, freeMem * 100.f / totalMem, max >> 10, num, id);
//				
//				ImGui::TreePop();
//			}
//
//			if (ImGui::TreeNode("[ReportConfig](3)"))
//			{
//				const char* itemsType[] = { "MDR_DumpMemory", "MDR_ShowUsage", "MDR_ShowUsageByFile", "MDR_ShowProfile", "MDR_DumpHeapStructure" };
//				static int item_currentType = 0;
//				if (ImGui::Combo("Type", &item_currentType, itemsType, IM_ARRAYSIZE(itemsType)))
//				{
//					int temp_val = item_currentType - 1;
//					//call listener
//				}
//
//				const char* itemsIsForAll[] = { "DL_FALSE", "DL_TRUE" };
//				static int item_currentIsForAll = 0;
//				if (ImGui::Combo("IsForAll", &item_currentIsForAll, itemsIsForAll, IM_ARRAYSIZE(itemsIsForAll)))
//				{
//					int temp_val = item_currentIsForAll - 1;
//					//call listener
//				}
//
//				const char* itemsOption[] = { "MDR_DumpMemory_Light", "MDR_DumpMemory_Detail", "MDR_ShowUsageByFile_Tree", "MDR_ShowUsageByFile_MemoryUsage", "MDR_ShowUsageByFile_BlockNumber", "MDR_DumpHeapStructure_HumanReadable", "MDR_DumpHeapStructure_CSV" };
//				static int item_currentOption = 0;
//				if (ImGui::Combo("Option", &item_currentOption, itemsOption, IM_ARRAYSIZE(itemsOption)))
//				{
//					int temp_val = item_currentOption - 1;
//					//call listener
//				}
//			}
//
//			ImGui::TreePop();
//		}
//
//		if (ImGui::TreeNode("[Perf MAN]"))
//		{
//			if (ImGui::TreeNode("[HG GPU]"))
//			{
//
//
//				ImGui::TreePop();
//			}
//
//			if (ImGui::TreeNode("[HG CPU]"))
//			{
//
//
//				ImGui::TreePop();
//			}
//
//			if (ImGui::TreeNode("[SYS CPU]"))
//			{
//
//
//				ImGui::TreePop();
//			}
//
//			if (ImGui::TreeNode("[GAME CPU]"))
//			{
//
//
//				ImGui::TreePop();
//			}
//
//			if (ImGui::TreeNode("[TASK CPU]"))
//			{
//
//
//				ImGui::TreePop();
//			}
//
//			if (ImGui::TreeNode("[MENU CPU]"))
//			{
//
//
//				ImGui::TreePop();
//			}
//
//			if (ImGui::TreeNode("[EVENT CPU]"))
//			{
//
//
//				ImGui::TreePop();
//			}
//
//			if (ImGui::TreeNode("[CHR CPU]"))
//			{
//
//
//				ImGui::TreePop();
//			}
//
//
//
//			ImGui::TreePop();
//		}
//
//		if (ImGui::TreeNode("[HG MAN]"))
//		{
//			if (ImGui::TreeNode("[FPS]"))
//			{
//
//
//				ImGui::TreePop();
//			}
//
//			ImGui::TreePop();
//		}
//	}
//}