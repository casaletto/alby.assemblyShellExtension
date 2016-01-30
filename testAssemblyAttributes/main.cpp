#include "stdafx.h"
#include "stringHelper.h" 
#include "exception.h" 
#include "sprintf.h"
#include "process.h"
#include "helper.h" 

/*

alby's c++ wide character best bet:

	- use windows xxxW functions whereever possible
	- use std::wstring internally
	- use std::string  externally, ie cout, file io
	- repeat: never ever send utf16 wstring's to io, only ever send utf8 string's

*/

int wmain( int argc, wchar_t* argv[] )
{
	int rc = 1 ;

	alby::helper  h   ;
	alby::sprintf msg ;
	alby::sprintf err ;
	alby::process pr  ;
	std::wstring  exe ;
	std::wstring  parameter ;

	msg = alby::sprintf( L"testAssemblyAttributes [start]" ) ;
	msg.debug() ;

	try
	{
		auto args = h.argvToVector( argc, argv ) ;

		h.getArguments( args, exe, parameter ) ;
		auto childrc = pr.exec( exe, parameter ) ;

		// dump output
		auto theStdout = alby::stringHelper::trim( pr.getStdout() ) ;
		auto theStderr = alby::stringHelper::trim( pr.getStderr() ) ;

		// process the output 
		if ( theStderr.size() > 0 )
			throw alby::exception( theStderr, __FILE__, __LINE__ ) ;

		if ( childrc != 0 )
			throw alby::exception( L"The child process returned a non zero exit code of " + std::to_wstring( childrc ), __FILE__, __LINE__ ) ;

		// transform the flat string to a dictionary
		auto dic = alby::helper::toMap(theStdout, L'\n', L'|' ) ;
	
		// dump the dic, this is the money shot
		for ( auto k : dic )
		{
			auto str = alby::sprintf( L"#", k.first, L"# = [", k.second, L"]" ) ;
			str.stdoutput() ;
		}

		rc = 0 ;  
	}
	catch( const alby::exception& ex )     
	{
		err = alby::sprintf( L"EXCEPTION\n", ex.what() ) ;
		err.debug();
		err.stderror();
	}
	catch( const std::exception& ex ) 
	{
		err = alby::sprintf( L"EXCEPTION\n", ex.what() ) ;
		err.debug();
		err.stderror();
	}
	catch( ... ) 
	{
		err = L"EXCEPTION\n..." ;
		err.debug();
		err.stderror();
	}

	msg = alby::sprintf( L"testAssemblyAttributes [finish] [", rc, L"]" );
	msg.debug() ;

	return rc ;
}

