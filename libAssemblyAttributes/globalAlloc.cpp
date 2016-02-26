#include "stdafx.h"
#include "stringHelper.h"
#include "exception.h" 
#include "sprintf.h"
#include "globalAlloc.h"

using namespace alby::assemblyAttributes::lib ;

globalAlloc::globalAlloc( SIZE_T bytes )
{
	//auto msg = lib::sprintf( L"globalAlloc [const]" ) ;
	//msg.debug();

	_bytes = bytes ;
	_handle = ::GlobalAlloc( GMEM_FIXED | GMEM_ZEROINIT, bytes ) ;

	if ( _handle == NULL )
		 throw lib::exception( L"GlobalAlloc() failed.", __FILE__, __LINE__ ) ;
}

globalAlloc::~globalAlloc() 
{
	//auto msg = lib::sprintf( L"globalAlloc [destr]" ) ;
	//msg.debug();

	if ( _handle != NULL )
		::GlobalFree( _handle ) ;
}

SIZE_T
globalAlloc::getBytes()
{
	return _bytes ;
}

void
globalAlloc::clear()
{
	if ( _handle != NULL )
		::ZeroMemory( _handle, _bytes ) ;
}

HGLOBAL
globalAlloc::detach()
{
	auto h = _handle ;
	_handle = NULL ;

	return h ;
}
