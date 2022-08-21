#pragma once 
 
namespace Backend // Removed 
{ 
	SHORT __stdcall skGetAsyncKeyState( int vKey )
	{ 
		return GetAsyncKeyState( vKey );
	}
	HMODULE __stdcall skGetModuleHandleA( LPCSTR lpModuleName )
	{
		return GetModuleHandleA( lpModuleName );
	}  
}