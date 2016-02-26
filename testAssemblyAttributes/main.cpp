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

//ALBY put in the  git attributes, and upload the picture to git hub 

//ALBY notes:
// run as admin:
// regsvr32 /s    alby.assemblyShellExtension.dll
// regsvr32 /u /s alby.assemblyShellExtension.dll

void testLoadedModules() ;
void testUtf8();
void testCom() ;
void testGetAssemblyAttributes( int argc, wchar_t* argv[] ) ;

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
		testLoadedModules() ;
		testUtf8() ;
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

void testUtf8()
{
	auto unicodeOrig = L"[languages of teh world Владивосто́к 日本国 すし 寿司 鮨 鮨飯 대한민국 大韓民國  سلطان سليمان اول  中华人民共和国 中華人民共和國   י   ְרוּשָׁלַ        ִם     القُدس (עיר הקודש,  سلطان سليمان اول  المملكة العربية السعودية a האקדמיה ללשון העברית  Cos'è questa cosa?  español? D'où êtes-vous À bientôt Ich heiße Was möchten Sie Wohin fährt dieser Bus मैं अच्छा हूँ, धन्यवाद। और आप?  ¡Hola! ¿Cómo está usted?]" ;

	std::wstring wstr1 = unicodeOrig ;
	std::cout << wstr1.size() << std::endl ;

	auto str1 = lib::stringHelper::ws2s( wstr1 ) ;
	std::cout << str1.size() << std::endl;
	std::cout << str1 << std::endl ;

	auto wstr2 = lib::stringHelper::s2ws( str1 ) ;
	std::cout << wstr2.size() << std::endl ;
}

void testLoadedModules()
{
	auto hCurrentProcess = ::GetCurrentProcess() ;

	auto list = lib::helper::getLoadedModules( hCurrentProcess ) ;

	for ( auto i : list )
		  lib::sprintf( i ).stdOutput() ;
}


