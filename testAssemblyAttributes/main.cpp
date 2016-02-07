﻿#include "stdafx.h"
#include "..\libAssemblyAttributes\stringHelper.h"
#include "..\libAssemblyAttributes\exception.h" 
#include "..\libAssemblyAttributes\sprintf.h"
#include "..\libAssemblyAttributes\process.h"
#include "..\libAssemblyAttributes\comEnvironment.h" 
#include "..\libAssemblyAttributes\helper.h" 

#import "..\bin\assemblyShellExtension.tlb" 

namespace lib = alby::assemblyAttributes::lib ;

void testCom() ;
void testGetAssemblyAttributes( int argc, wchar_t* argv[] ) ;

/*

alby's c++ wide character best bet:

- use windows xxxW functions whereever possible 
- use std::wstring internally
- use std::string  externally, ie cout, file io
- repeat: never ever send utf16 wstring's to io, only ever send utf8 string's

*/

// wmain: program entry point
// must be a global function
// cant be in a namespace
// not even in the :: global namespace

int wmain( int argc, wchar_t* argv[] ) 
{
	int rc = 1 ;

	lib::sprintf msg ;
	lib::sprintf err ;

	msg = lib::sprintf( L"testAssemblyAttributes [start]" ) ;
	msg.debug() ;

	try
	{
		testCom();
		testGetAssemblyAttributes( argc, argv ) ;

		rc = 0 ;  
	}
	catch (const lib::exception& ex)
	{
		err = lib::sprintf(L"EXCEPTION\n", ex.what());
		err.debug();
		err.stderror();
	}
	catch( const std::exception& ex ) 
	{
		err = lib::sprintf(L"EXCEPTION\n", ex.what());
		err.debug();
		err.stderror();
	}
	catch( ... ) 
	{
		err = L"EXCEPTION\n..." ;
		err.debug();
		err.stderror();
	}

	msg = lib::sprintf(L"testAssemblyAttributes [finish] [", rc, L"]");
	msg.debug() ;

	return rc ;
}

void testCom()
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ff485839(v=vs.85).aspx

	#define MY_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) const GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
	MY_DEFINE_GUID(CLSID_ALBY, 0xFF000017, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

	try
	{
		lib::comEnvironment com ;  

		//ALBY
		auto libid = __uuidof( assemblyShellExtensionLib::__assemblyShellExtensionLib ) ;//ALBY how to 
		auto msg = lib::sprintf( libid.Data1, libid.Data2, libid.Data3, libid.Data4 ) ;
		msg.stdoutput() ;

		CComPtr<IUnknown> palby;
		auto hr = palby.CoCreateInstance( __uuidof( assemblyShellExtensionLib::assemblyShelllPropertyPage  ) ) ;
		if ( FAILED(hr) ) throw _com_error( hr ) ;

		CComPtr<IUnknown> punk ;
		hr = punk.CoCreateInstance( CLSID_StaticDib ) ; //CLSID_ALBY ) ; //CLSID_StaticDib );
		if ( FAILED(hr) ) throw _com_error( hr ) ;

		if (punk.p == nullptr)
			throw lib::exception(L"null ptr punk", __FILE__, __LINE__ );

		msg = lib::sprintf( punk.p ) ;
		msg.stdoutput() ;

		CComQIPtr<IDataObject> pdata = punk;
		if ( pdata.p == nullptr ) 
			throw lib::exception( L"null ptr pdata", __FILE__, __LINE__ ) ; 

		msg = lib::sprintf( pdata.p ) ;
		msg.stdoutput();

		CComQIPtr<IAccessible> pacc = pdata ;
		if ( pacc.p == nullptr )
			throw lib::exception( L"null ptr pacc", __FILE__, __LINE__);

		msg = lib::sprintf( pacc.p ) ;
		msg.stdoutput();
	}
	catch( const _com_error& ex )
	{
		auto msg = lib::sprintf( L"0x", std::hex, ex.Error(), L" ", ex.ErrorMessage() ) ;

		throw lib::exception( msg.ws(), __FILE__, __LINE__ ) ;
	}
}

void testGetAssemblyAttributes( int argc, wchar_t* argv[] )
{
	lib::helper  h;
	lib::sprintf msg;
	lib::sprintf err;
	lib::process pr;
	std::wstring exe;
	std::wstring parameter;

	auto args = h.argvToVector(argc, argv);

	h.getArguments(args, exe, parameter);

	// call the child .net process
	auto childrc = pr.exec(exe, parameter);

	// get output from child .net process
	auto theStdout = lib::stringHelper::trim(pr.getStdout());
	auto theStderr = lib::stringHelper::trim(pr.getStderr());

	// process the output 
	if (theStderr.size() > 0)
		throw lib::exception(theStderr, __FILE__, __LINE__);

	if (childrc != 0)
		throw lib::exception(L"The child process returned a non zero exit code of " + std::to_wstring(childrc), __FILE__, __LINE__);

	// transform the flat string to a dictionary
	auto dic = lib::helper::toMap(theStdout, L'\n', L'|');

	// dump the dic, this is the money shot
	for (auto k : dic)
	{
		auto str = lib::sprintf(L"#", k.first, L"# = [", k.second, L"]");
		str.stdoutput();
	}
}

