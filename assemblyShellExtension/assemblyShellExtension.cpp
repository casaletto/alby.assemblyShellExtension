#include "stdafx.h"
#include "resource.h"
#include "assemblyShellExtension_i.h"
#include "dllmain.h"
#include "xdlldata.h"

#include "..\libAssemblyAttributes\stringHelper.h"
#include "..\libAssemblyAttributes\exception.h" 
#include "..\libAssemblyAttributes\sprintf.h"
#include "..\libAssemblyAttributes\process.h"
#include "..\libAssemblyAttributes\comEnvironment.h" 
#include "..\libAssemblyAttributes\helper.h" 

using namespace ATL;  

namespace lib = alby::assemblyAttributes::lib ;

STDAPI DllCanUnloadNow(void)
{

#ifdef _MERGE_PROXYSTUB
	HRESULT hr = PrxDllCanUnloadNow();
	if (hr != S_OK)
		return hr;
#endif

	auto rc = _AtlModule.DllCanUnloadNow();

	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [DllCanUnloadNow] ", rc ) ;
	msg.debug() ;

	return rc ;
}

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{

#ifdef _MERGE_PROXYSTUB
	HRESULT hr = PrxDllGetClassObject(rclsid, riid, ppv);
	if (hr != CLASS_E_CLASSNOTAVAILABLE)
		return hr;
#endif

	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllRegisterServer(void)
{
	HRESULT hr = _AtlModule.DllRegisterServer();

#ifdef _MERGE_PROXYSTUB
	if (FAILED(hr))
		return hr;
	hr = PrxDllRegisterServer();
#endif

	return hr;
}

STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();

#ifdef _MERGE_PROXYSTUB
	if (FAILED(hr))
		return hr;
	hr = PrxDllRegisterServer();
	if (FAILED(hr))
		return hr;
	hr = PrxDllUnregisterServer();
#endif

	return hr;
}

STDAPI DllInstall(BOOL bInstall, _In_opt_  LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if (pszCmdLine != NULL)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ATL::AtlSetPerUserRegistration(true);
		}
	}

	if (bInstall)
	{
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}

	return hr;
}

