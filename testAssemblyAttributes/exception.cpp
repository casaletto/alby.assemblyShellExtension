#include "stdafx.h"
#include "stringHelper.h"
#include "exception.h"

using namespace alby::assemblyAttributes::lib ;

exception::~exception() throw()
{
}

exception::exception() throw()
{
}

exception::exception( const std::wstring& message ) throw()
{
	this->_message = message;
}

exception::exception( const std::wstring& message, const char* theFilename, int theLine ) throw()
{
	this->_message = message ;

	auto gle = this->getLastError() ;
	gle = lib::stringHelper::trim(gle);

	if ( gle.size() > 0 )
	{ 
		this->_message += L"\n";
		this->_message += gle ;
	}

	std::string filename( theFilename ) ;

	if ( filename.size() > 0 )
	{
		this->_message += L"\nat ";
		this->_message += lib::stringHelper::s2ws( filename ) ;

		if ( theLine > 0 )
		{
			this->_message += L" line ";
			this->_message += std::to_wstring( theLine ) ;
		}
	}
}

exception::exception( const exception& rhs ) throw()
{
	this->_message = rhs._message ;
}

exception& exception::operator=( const exception& rhs ) throw()
{
	this->_message = rhs._message ;

	return *this ;
}

std::wstring exception::what() const throw()
{
	return this->_message ;
}

std::wstring exception::getLastError()
{
	wchar_t sz[ BUFFER_SIZE+10 ] ;
	::ZeroMemory( sz, sizeof(sz) ) ;

	auto errorCode = ::GetLastError() ;
	if ( errorCode == 0 )
		return std::wstring() ;

	::FormatMessageW(
		FORMAT_MESSAGE_FROM_SYSTEM, 
		NULL, 
		errorCode, 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		sz, 
		sizeof(sz), 
		NULL ) ;

	::SetLastError( 0 ) ;

	return std::wstring( sz ) ;
}

