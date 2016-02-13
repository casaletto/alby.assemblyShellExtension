#include "stdafx.h"
#include "stdafx.h"
#include "stringHelper.h"
#include "sprintf.h"
#include "exception.h" 
#include "stgMedium.h"

using namespace alby::assemblyAttributes::lib ;

stgMedium::stgMedium( IDataObject *pDataObject, FORMATETC& formatEtc )
{
	auto msg = lib::sprintf( L"stgMedium [const]" ) ;
	//msg.debug();

	try
	{
		auto hr = pDataObject->GetData( &formatEtc, &_stgMedium ) ; 
		if ( FAILED(hr) ) throw _com_error(hr) ;

		_ok = true ;
	}
	catch ( const _com_error& ex )
	{
		msg = lib::sprintf( L"0x", std::hex, ex.Error(), L" ", ex.ErrorMessage() ) ;
		throw lib::exception( msg.ws(), __FILE__, __LINE__) ;
	}
}

stgMedium::~stgMedium()
{
	auto msg = lib::sprintf(L"stgMedium [destr]");
	//msg.debug();

	if ( _ok )
		::ReleaseStgMedium( &_stgMedium ) ;
}

STGMEDIUM 
stgMedium::getStgMedium()
{
	return _stgMedium ;
}
