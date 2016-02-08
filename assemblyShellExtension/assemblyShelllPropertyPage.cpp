#include "stdafx.h"
#include "..\libAssemblyAttributes\stringHelper.h"
#include "..\libAssemblyAttributes\exception.h" 
#include "..\libAssemblyAttributes\sprintf.h"
#include "..\libAssemblyAttributes\process.h"
#include "..\libAssemblyAttributes\comEnvironment.h" 
#include "..\libAssemblyAttributes\helper.h" 
#include "assemblyShelllPropertyPage.h"

using namespace ATL ; 

namespace lib = alby::assemblyAttributes::lib;

assemblyShelllPropertyPage::assemblyShelllPropertyPage()
{
	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [constructor]");
	msg.debug();
}

HRESULT assemblyShelllPropertyPage::FinalConstruct()
{
	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [final constructor]");
	msg.debug();

	return S_OK;
}

void assemblyShelllPropertyPage::FinalRelease()
{
	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [final release]");
	msg.debug();
}

STDMETHODIMP assemblyShelllPropertyPage::HelloWorld( BSTR aString, BSTR* returnedBStr)
{
	auto msg = lib::sprintf( L"assemblyShelllPropertyPage [HelloWorld]" ) ;
	msg.debug();

	lib::sprintf str( aString, L" ", lib::helper::getDateTime() ) ;
	str.debug() ;

	::_bstr_t result( str.ws().c_str() ) ;

	*returnedBStr = result.Detach() ;

	return S_OK;
}
