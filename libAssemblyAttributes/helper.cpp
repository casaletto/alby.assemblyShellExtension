#include "stdafx.h"
#include "stringHelper.h"
#include "exception.h" 
#include "sprintf.h"
#include "helper.h"

using namespace alby::assemblyAttributes::lib ; 

helper::helper()
{
}

helper::~helper()
{
}

std::vector<std::wstring> 
helper::argvToVector( int argc, wchar_t* argv[] )
{
	std::vector<std::wstring> args ;
	
	for (auto i = 0; i < argc; i++)
		args.push_back(argv[i]);

	return args ;
}

void 
helper::getArguments( std::vector<std::wstring>& args, std::wstring& inspector, std::wstring& inspectee )
{
	inspector = std::wstring() ;
	inspectee = std::wstring() ;

	if ( args.size() >= 2 )
		inspector = args[1] ;

	if ( args.size() >= 3 )
		 inspectee = args[2] ;
}

std::map<std::wstring, std::wstring> 
helper::toMap( const std::wstring str, wchar_t majorDelim, wchar_t minorDelim )
{
	std::map<std::wstring, std::wstring> dic ;

	auto list = lib::stringHelper::split( str, majorDelim ) ;

	for ( auto line : list )
	{
		auto line2 = lib::stringHelper::trim( line ) ;
		if ( line2.size() == 0 ) continue ;

		auto kvpair = lib::stringHelper::split( line2, minorDelim ) ;

		if ( kvpair.size() == 0 ) continue ;
		if ( kvpair.size() == 1 )
			 kvpair.push_back( std::wstring() ) ;

		auto key   = lib::stringHelper::trim( kvpair[0] ) ;
		auto value = lib::stringHelper::trim( kvpair[1] ) ;
	
		if ( key.size() == 0 ) continue ;

		dic[ key ] = value ;
	}

	return dic ;
}

std::wstring 
helper::getDateTime()
{
	auto t  = std::time( nullptr ) ;
	auto tm = std::localtime( &t ) ;

	std::stringstream ss ;
	ss << std::put_time( tm, "%Y.%m.%d %H.%M.%S" ) ; 

	lib::sprintf msg( ss.str().c_str() ) ;

	return msg.ws() ;
}

