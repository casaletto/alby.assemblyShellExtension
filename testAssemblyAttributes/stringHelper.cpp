#include "stdafx.h"
#include "stringHelper.h"

using namespace alby ;

stringHelper::stringHelper()
{
}

stringHelper::~stringHelper()
{
}

std::wstring stringHelper::s2ws(const std::string& str)
{
	typedef std::codecvt_utf8<wchar_t> convert_typeX;

	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

std::string stringHelper::ws2s(const std::wstring& wstr)
{
	typedef std::codecvt_utf8<wchar_t> convert_typeX;

	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

const std::wstring stringHelper::__delimiters = L" \f\n\r\t\v";

std::wstring stringHelper::ltrim( const std::wstring& wstr )
{
	if ( wstr.size() == 0 ) return wstr ;

	return wstr.substr( wstr.find_first_not_of( __delimiters ) ) ;
}

std::wstring stringHelper::rtrim( const std::wstring& wstr )
{
	if ( wstr.size() == 0 ) return wstr ;

	return wstr.substr( 0, wstr.find_last_not_of( __delimiters ) + 1 ) ;
}

std::wstring stringHelper::trim( const std::wstring& wstr )
{
	return rtrim( ltrim( wstr ) ) ;
}

std::vector<std::wstring> stringHelper::split( const std::wstring& wstr, wchar_t delimiter )
{
	std::vector<std::wstring> result ;

	std::wstringstream ss( wstr ) ;
	std::wstring item ;

	while ( std::getline( ss, item, delimiter ) )
		result.push_back( item ) ;

	return result ;
}



