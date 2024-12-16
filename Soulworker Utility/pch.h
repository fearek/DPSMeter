#pragma once

#ifndef PCH_H
#define PCH_H

#ifdef _DEBUG
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif

#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800

#include <Windows.h>

#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")

#include <stdio.h>
#include <mutex>
#include <string>
#include <functional>
#include <time.h>
#include <array>
#include <comdef.h>
#include <locale>
#include <tchar.h>
#include <vector>
#include <algorithm>
#include <codecvt>
#include <filesystem>
#include <fstream> 
// DISCORD
#include "discord\discord.h"
// IMGUI
#include "imgui\imgui.h"
#include "imgui\backends\imgui_impl_win32.h"
#include "imgui\backends\imgui_impl_dx11.h"
#include "imgui\Custom.h"
#include "imgui\implot.h"
#include "imgui\implot_internal.h"
#include "imgui\imgui_filedialog.h"

// DirectX
#include <d3d11.h>
#include <dinput.h>


// SQLite3
#include "SQLite\include\sqlite3.h"

// tinyxml2
#include "tinyxml2\tinyxml2.h"

// Utility
#include ".\Util\Type.h"
#include ".\Util\Singleton.h"
#include ".\Util\Log.h"
#include ".\Util\ExceptionHandler.h"
#include ".\Util\CriticalSection.h"
#include ".\Util\MultiThreadSync.h"
#include ".\Util\MemoryPool.h"
#include ".\Language\Language.h"
#include ".\discord\DiscordPresence.h"



// Json
#include ".\Util\json.hpp"
using json = nlohmann::json;

#endif