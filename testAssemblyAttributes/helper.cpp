#include "stdafx.h"
#include "stringHelper.h" 
#include "exception.h" 
#include "helper.h"

using namespace alby ;

helper::helper()
{
}

helper::~helper()
{
}

std::vector<std::wstring> helper::argvToVector( int argc, wchar_t* argv[] )
{
	std::vector<std::wstring> args ;
	
	for (auto i = 0; i < argc; i++)
		args.push_back(argv[i]);

	return args ;
}

void helper::getArguments( std::vector<std::wstring>& args, std::wstring& inspector, std::wstring& inspectee )
{
	inspector = std::wstring() ;
	inspectee = std::wstring() ;

	if ( args.size() >= 2 )
		inspector = args[1] ;

	if ( args.size() >= 3 )
		 inspectee = args[2] ;
}

