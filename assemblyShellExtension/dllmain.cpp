// dllmain.cpp : Implementation of DllMain.



//ALBY remove unused files and commented out code


#include "stdafx.h"
#include "resource.h"
//#include "assemblyShellExtension_i.h"
#include "dllmain.h"

CassemblyShellExtensionModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
