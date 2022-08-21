#pragma once

#include <xmmintrin.h>
#include <emmintrin.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <d3d11.h>
#include <vector>
#include <string>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Header Files/Backend/Includes/MinHook/minhook.lib") 

#include "Header Files/Backend/Utility/XorString.h"
#include "Header Files/Backend/Utility/Memory.h"
#include "Header Files/Backend/WindowsHooks.h"
#include "Header Files/Backend/Utility/DynamicPad.h" 
#include "Header Files/Backend/Utility/Vectors.h"
#include "Header Files/Backend/Utility/Math.h"
#include "Header Files/Game/Anvil.hh"
#include "Header Files/Backend/Includes/ImGui/imgui.h" 
#include "Header Files/Backend/Includes/ImGui/imgui_internal.h"
#include "Header Files/Backend/Includes/ImGui/imgui_impl_win32.h"
#include "Header Files/Backend/Includes/ImGui/imgui_impl_dx11.h"
#include "Header Files/Backend/Includes/ImGui/AddOns/Font.h"
#include "Header Files/Backend/Includes/ImGui/AddOns/imguipp.h"
#include "Header Files/Backend/Includes/ImGui/AddOns/imgui_animated.h"
#include "Header Files/UserInterface.h"  
#include "Header Files/Client.h" 
#include "Header Files/Backend/Includes/MinHook/MinHook.h" 
#include "Header Files/Backend/Renderer/Renderer.h"
#include "Header Files/Backend/PresentHook/PresentHook.h" 

BOOL DoOnce;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if ( !DoOnce )
    {
        DoOnce = TRUE; 
        CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE ) PresentHook::Initialize, 0, 0, 0 ); 
    }
    return TRUE;
}

