#include "stdafx.h"
#include "stringHelper.h"
#include "exception.h" 
#include "sprintf.h"
#include "comEnvironment.h"

using namespace alby::assemblyAttributes::lib ;

comEnvironment::comEnvironment()
{
	auto hr = ::CoInitializeEx( NULL, COINIT_APARTMENTTHREADED ) ;

	if ( FAILED(hr) ) throw _com_error( hr ) ;
}

comEnvironment::~comEnvironment()
{
	::CoUninitialize();
}
