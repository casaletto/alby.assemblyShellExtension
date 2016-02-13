#include "stdafx.h"
#include "stringHelper.h"

using namespace alby::assemblyAttributes::lib ;

stringHelper::stringHelper()
{
}

stringHelper::~stringHelper()
{
}

std::wstring 
stringHelper::s2ws(const std::string& str)
{
	typedef std::codecvt_utf8<wchar_t> convert_typeX;

	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

std::string 
stringHelper::ws2s(const std::wstring& wstr)
{
	typedef std::codecvt_utf8<wchar_t> convert_typeX;

	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

const std::wstring stringHelper::__delimiters = L" \f\n\r\t\v";

std::wstring 
stringHelper::ltrim( const std::wstring& wstr )
{
	if ( wstr.size() == 0 ) return wstr ;

	return wstr.substr( wstr.find_first_not_of( __delimiters ) ) ;
}

std::wstring 
stringHelper::rtrim( const std::wstring& wstr )
{
	if ( wstr.size() == 0 ) return wstr ;

	return wstr.substr( 0, wstr.find_last_not_of( __delimiters ) + 1 ) ;
}

std::wstring 
stringHelper::trim( const std::wstring& wstr )
{
	return rtrim( ltrim( wstr ) ) ;
}

std::vector<std::wstring> 
stringHelper::split( const std::wstring& wstr, wchar_t delimiter )
{
	std::vector<std::wstring> result ;

	std::wstringstream ss( wstr ) ;
	std::wstring item ;

	while ( std::getline( ss, item, delimiter ) )
		result.push_back( item ) ;

	return result ;
}

bool 
stringHelper::endsWith( const std::wstring& str, const std::wstring& suffix, bool caseSensitive )
{
	if ( str.size()    == 0         ) return false ;
	if ( suffix.size() == 0         ) return false ;
	if ( suffix.size() > str.size() ) return false ;

	auto str2    = std::move( str    ) ;
	auto suffix2 = std::move( suffix ) ;

	if ( ! caseSensitive ) // case insensitive, convert to upper case
	{
		str2	= stringHelper::toUpper( str2    ) ;
		suffix2	= stringHelper::toUpper( suffix2 ) ;
	}

	auto pos = str.rfind( suffix2 ) ;

	if ( pos == std::wstring::npos ) return false ;

	return str2.size() == suffix2.size() + pos ;
}

bool
stringHelper::startsWith( const std::wstring& str, const std::wstring& prefix, bool caseSensitive )
{
	if ( str.size()    == 0         ) return false ;
	if ( prefix.size() == 0         ) return false ;
	if ( prefix.size() > str.size() ) return false ;

	auto str2    = std::move( str    ) ;
	auto prefix2 = std::move( prefix ) ;

	if ( ! caseSensitive ) // case insensitive, convert to upper case
	{
		str2	= stringHelper::toUpper( str2    ) ;
		prefix2	= stringHelper::toUpper( prefix2 ) ;
	}

	auto pos = str.find( prefix2 ) ;

	if ( pos == std::wstring::npos ) return false ;

	return pos == 0 ;
}

std::wstring 
stringHelper::toUpper( const std::wstring& str )
{
	if ( str.size() == 0 ) return str ;

	auto result = std::move( str ) ; 

	::CharUpperW( (LPWSTR) result.c_str() ) ;

	return result ;

	/*
	auto i = 0 ; 
	std::for_each( 
		str.begin(), 
		str.end(), 
		[ &result, locale, &i ]( const WCHAR c ) 
		{ 
			result[i++] = std::toupper( c, locale ) ;
		});
	*/
}

std::wstring
stringHelper::toLower( const std::wstring& str )
{
	if ( str.size() == 0 ) return str ;

	auto result = std::move( str ) ; 

	::CharLowerW( (LPWSTR) result.c_str() ) ;

	return result ;
}

