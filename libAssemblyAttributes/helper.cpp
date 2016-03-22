#include "stdafx.h"
#include "stringHelper.h"
#include "exception.h" 
#include "sprintf.h"
#include "globalAlloc.h"
#include "helper.h"

using namespace alby::assemblyAttributes::lib ; 

helper::helper()
{
}

helper::~helper()
{
}

const std::wstring 
helper::CSHARP_ASSEMBLY_ATTRIBUTES_EXE_64 = L"alby.assemblyAttributes.exe" ;

const std::wstring
helper::CSHARP_ASSEMBLY_ATTRIBUTES_EXE_32 = L"alby.assemblyAttributes32.exe";

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
helper::mapToString( std::map<std::wstring, std::wstring> map ) 
{
	std::wstring str ;

	for ( auto k : map )
	{ 
		auto tmp = lib::sprintf( k.first, ":\r\n", k.second ).ws() ;
		tmp = lib::stringHelper::trim( tmp ) ;

		str = lib::sprintf( str, tmp, L"\r\n\r\n" ).ws() ;
	}

	return lib::stringHelper::trim( str ) ;
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

std::wstring
helper::getCurrentModuleDirectory()
{
	HMODULE hmodule = NULL ;

	::GetModuleHandleExW(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, 
		(LPCWSTR) getCurrentModuleDirectory, 
		&hmodule ) ;

	if ( hmodule == NULL )
		 throw lib::exception( L"GetModuleHandleEx() failed.", __FILE__, __LINE__ ) ;

	auto sz = lib::globalAlloc( (helper::EXTENTED_MAX_PATH + 2) * sizeof(WCHAR));
	auto p = sz.getPointer<LPWSTR>();

	auto rc = ::GetModuleFileNameW( hmodule, p, helper::EXTENTED_MAX_PATH ) ;
	if ( rc == 0 )
		 throw lib::exception( L"GetModuleFileName() failed.", __FILE__, __LINE__ ) ;

	std::wstring result = p ;

	auto pos = result.rfind( L"\\" ) ;
	if ( pos == std::wstring::npos )
		 throw lib::exception( L"rfind(): cant find \\", __FILE__, __LINE__);

	result = result.substr( 0, pos ) ;

	return result ;
}

std::vector<std::wstring>
helper::getLoadedModules( HANDLE hProcess )
{
	std::vector<std::wstring> list ;

	HMODULE rng ;
	DWORD bytesRequired ;

	auto rc = ::EnumProcessModules( hProcess, &rng, 0, &bytesRequired ) ;
	if ( rc == 0 ) 
		 throw lib::exception( L"EnumProcessModules() failed.", __FILE__, __LINE__ ) ;

	auto mem = lib::globalAlloc( bytesRequired ) ;
	auto pmem = mem.getPointer<HMODULE*>();

	rc = ::EnumProcessModules( hProcess, pmem, (DWORD) mem.getBytes(), &bytesRequired ) ;
	if ( rc == 0 )
		 throw lib::exception( L"EnumProcessModules() failed.", __FILE__, __LINE__ ) ;

	auto moduleCount = mem.getBytes() / sizeof( HMODULE ) ;

	auto sz  = lib::globalAlloc( (helper::EXTENTED_MAX_PATH + 2) * sizeof(WCHAR) ) ;
	auto psz = sz.getPointer<LPWSTR>() ;

	for ( auto i = 0 ; i < moduleCount ; i++ )
	{
		sz.clear() ;

		rc = ::GetModuleFileNameW( pmem[i], psz, helper::EXTENTED_MAX_PATH ) ;
		if ( rc == 0 )
			 throw lib::exception( L"GetModuleFileName() failed.", __FILE__, __LINE__ ) ;

		list.push_back( psz ) ;
	}

	return list ;
}





