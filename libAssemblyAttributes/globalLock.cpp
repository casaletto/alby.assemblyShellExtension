#include "stdafx.h"
#include "stringHelper.h"
#include "exception.h" 
#include "sprintf.h"
#include "globalLock.h"

using namespace alby::assemblyAttributes::lib ;

globalLock::globalLock( HGLOBAL h )
{
	auto msg = lib::sprintf( L"globalLock [const]" );
	//msg.debug();

	if ( h == NULL )
		throw lib::exception( L"GlobalLock(): handle is null.", __FILE__, __LINE__ ) ;

	_handle  = h ;
	_pointer = ::GlobalLock( h ) ;

	if ( _pointer == NULL )
		 throw lib::exception( L"GlobalLock() failed.", __FILE__, __LINE__ ) ;
}

globalLock::~globalLock()
{
	auto msg = lib::sprintf( L"globalLock [const]" ) ;
	//msg.debug();

	if ( _handle != NULL && _pointer != NULL )
		 ::GlobalUnlock( _handle ) ;
}
