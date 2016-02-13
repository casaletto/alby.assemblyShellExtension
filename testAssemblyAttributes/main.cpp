#include "stdafx.h"
#include "..\libAssemblyAttributes\stringHelper.h"
#include "..\libAssemblyAttributes\exception.h" 
#include "..\libAssemblyAttributes\sprintf.h"
#include "..\libAssemblyAttributes\process.h"
#include "..\libAssemblyAttributes\comEnvironment.h" 
#include "..\libAssemblyAttributes\globalAlloc.h" 
#include "..\libAssemblyAttributes\helper.h" 

#import "..\bin\assemblyShellExtension.tlb" 

namespace lib = alby::assemblyAttributes::lib ;

void testCom() ;
void testGetAssemblyAttributes( int argc, wchar_t* argv[] ) ;

// wmain: program entry point
// must be a global function
// cant be in a namespace
// not even in the :: global namespace


//ALBY TO DO: have to fire the exe from the cuurent folder of the ATL dll


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
	catch ( const lib::exception& ex )
	{
		err = lib::sprintf(L"EXCEPTION\n", ex.what());
		err.debug();
		err.stdError();
	}
	catch( const std::exception& ex ) 
	{
		err = lib::sprintf(L"EXCEPTION\n", ex.what());
		err.debug();
		err.stdError();
	}
	catch( ... ) 
	{
		err = L"EXCEPTION\n..." ;
		err.debug();
		err.stdError();
	}

	msg = lib::sprintf(L"testAssemblyAttributes [finish] [", rc, L"]");
	msg.debug() ;

	return rc ;
}

void testCom()
{
	// run as admin:
	// regsvr32 /s    alby.assemblyShellExtension.dll
	// regsvr32 /u /s alby.assemblyShellExtension.dll
	//ALBY https://msdn.microsoft.com/en-us/library/windows/desktop/ff485839(v=vs.85).aspx

	try
	{
		lib::comEnvironment com ;  

		lib::sprintf msg = lib::helper::getDateTime();
		msg.debug();

		assemblyShellExtensionLib::IassemblyShelllPropertyPagePtr p;

		auto hr = p.CreateInstance( __uuidof( assemblyShellExtensionLib::assemblyShelllPropertyPage ) ) ;
		if ( FAILED(hr) ) throw _com_error( hr ) ;

		_bstr_t p1 = L"BARNEY" ;
		auto result = p->HelloWorld( p1 ) ;

		msg = lib::sprintf( result.GetBSTR() ) ; 
		msg.stdOutput();

		/*
		CComQIPtr<IDataObject> pdata = punk;
		if ( pdata.p == nullptr ) 
			throw lib::exception( L"null ptr pdata", __FILE__, __LINE__ ) ; 

		msg = lib::sprintf( pdata.p ) ;
		msg.stdoutput();
		*/
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
		str.stdOutput();
	}
}

