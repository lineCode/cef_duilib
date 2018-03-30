#pragma once

#include <Windows.h>

#include "..\DuiLib\UIlib.h" 

using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, ".\\Release\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, ".\\Release\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, ".\\Release\\DuiLib_u.lib")
#   else
#       pragma comment(lib, ".\\Release\\DuiLib.lib")
#   endif
#endif 
 
#pragma comment(lib, ".\\Release\\libcef.lib")
#pragma comment(lib, ".\\Release\\libcef_dll_wrapper.lib") 
#pragma comment(lib, ".\\Release\\cef_sandbox.lib") 
