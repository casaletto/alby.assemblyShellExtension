#include "stdafx.h"
#include "stringHelper.h" 
#include "exception.h" 
#include "sprintf.h"
#include "process.h"
#include "helper.h" 

namespace lib = alby::assemblyAttributes::lib ;

/*

alby's c++ wide character best bet:

- use windows xxxW functions whereever possible
- use std::wstring internally
- use std::string  externally, ie cout, file io
- repeat: never ever send utf16 wstring's to io, only ever send utf8 string's

*/


//ALBY move the files to lib
//alby.assemblyAttribubtes.lib
// namespace alby::assemblyAttribubtes

//atl component
// alby.assemblyShellExtension.dll

//ALBY namespces
//helper.h namespace   alby.assemblyAttributes.lib


// wmain: program entry point
// must be a global function
// cant be in a namespace
// not even in the :: global namespace

int wmain( int argc, wchar_t* argv[] ) 
{
	int rc = 1 ;

	lib::helper  h   ;
	lib::sprintf msg ;
	lib::sprintf err ;
	lib::process pr  ;
	std::wstring exe ;
	std::wstring parameter ;

	msg = lib::sprintf( L"testAssemblyAttributes [start]" ) ;
	msg.debug() ;

	try
	{
		auto args = h.argvToVector( argc, argv ) ;

		h.getArguments( args, exe, parameter ) ;
		auto childrc = pr.exec( exe, parameter ) ;

		// dump output
		auto theStdout = lib::stringHelper::trim( pr.getStdout() ) ;
		auto theStderr = lib::stringHelper::trim( pr.getStderr() ) ;

		// process the output 
		if ( theStderr.size() > 0 )
			throw lib::exception( theStderr, __FILE__, __LINE__ ) ;

		if ( childrc != 0 )
			throw lib::exception( L"The child process returned a non zero exit code of " + std::to_wstring( childrc ), __FILE__, __LINE__ ) ;

		// transform the flat string to a dictionary
		auto dic = lib::helper::toMap(theStdout, L'\n', L'|' ) ;
	
		// dump the dic, this is the money shot
		for ( auto k : dic )
		{
			auto str = lib::sprintf(L"#", k.first, L"# = [", k.second, L"]");
			str.stdoutput() ;
		}

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

