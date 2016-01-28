#include "stdafx.h"
#include "stringHelper.h" 
#include "exception.h" 
#include "sprintf.h"
#include "process.h"
#include "helper.h" 

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
		rc = pr.exec( exe, parameter ) ;

		// dump output
		auto theStdout = pr.getStdout() ;
		auto theStderr = pr.getStderr() ;

		// process the output 
		if ( theStdout.size() > 0 )
			std::cout << alby::stringHelper::ws2s( theStdout ) << std::endl ;

		if ( theStderr.size() > 0 )
			std::cout << alby::stringHelper::ws2s( theStderr ) << std::endl ;

		if ( rc != 0 )
			throw alby::exception( L"child process returned non zero return code" ) ;

		rc = 0 ;
	}
	catch( const alby::exception& ex ) 
	{
		err = alby::sprintf( L"EXCEPTION\n", ex.what() ) ;
		err.debug();
		err.console();
	}
	catch( const std::exception& ex ) 
	{
		err = alby::sprintf( L"EXCEPTION\n", ex.what() ) ;
		err.debug();
		err.console();
	}
	catch( ... ) 
	{
		err = L"EXCEPTION\n..." ;
		err.debug();
		err.console();
	}

	msg = alby::sprintf( L"testAssemblyAttributes [finish] [", rc, L"]" );
	msg.debug() ;

	return rc ;
}

