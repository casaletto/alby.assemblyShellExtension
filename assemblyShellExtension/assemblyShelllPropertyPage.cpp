#include "stdafx.h"
#include "..\libAssemblyAttributes\stringHelper.h"
#include "..\libAssemblyAttributes\exception.h" 
#include "..\libAssemblyAttributes\sprintf.h"
#include "..\libAssemblyAttributes\process.h"
#include "..\libAssemblyAttributes\comEnvironment.h" 
#include "..\libAssemblyAttributes\globalAlloc.h" 
#include "..\libAssemblyAttributes\globalLock.h" 
#include "..\libAssemblyAttributes\stgMedium.h" 
#include "..\libAssemblyAttributes\helper.h" 
#include "assemblyShelllPropertyPage.h"

using namespace ATL ; 

namespace lib = alby::assemblyAttributes::lib;

assemblyShelllPropertyPage::assemblyShelllPropertyPage()
{
	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [constructor]");
	//msg.debug();
}

HRESULT assemblyShelllPropertyPage::FinalConstruct()
{
	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [final constructor]");
	//msg.debug();

	return S_OK;
}

void 
assemblyShelllPropertyPage::FinalRelease()
{
	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [final release]");
	//msg.debug();
}

STDMETHODIMP 
assemblyShelllPropertyPage::HelloWorld( BSTR aString, BSTR* returnedBStr)
{
	auto msg = lib::sprintf( L"assemblyShelllPropertyPage [HelloWorld]" ) ;
	msg.debug();

	lib::sprintf str( aString, L" ", lib::helper::getDateTime() ) ;
	str.debug() ;

	::_bstr_t result( str.ws().c_str() ) ;

	*returnedBStr = result.Detach() ;

	return S_OK;
}

STDMETHODIMP 
assemblyShelllPropertyPage::Initialize
(
	PCIDLIST_ABSOLUTE	pidlFolder,
	IDataObject			*pDataObject,
	HKEY				hkeyProgID
)
{
	const HRESULT HR_ABORT = E_INVALIDARG ;

	FORMATETC formatetc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL } ;

	std::wstring filename ;

	auto msg = lib::sprintf( L"assemblyShelllPropertyPage [Initialize]" ) ;
	//msg.debug() ;

	try
	{
		lib::stgMedium  stgMedium( pDataObject, formatetc ) ;
		lib::globalLock hdrop( stgMedium.getStgMedium().hGlobal ) ;	

		auto fileCount = ::DragQueryFileW( hdrop.getPointer<HDROP>() , 0xFFFFFFFF, NULL, 0 ) ;
		if ( fileCount == 0 ) 
			 throw lib::exception( L"DragQueryFileW(): no files.", __FILE__, __LINE__ ) ;

		auto firstFile = lib::globalAlloc( (EXTENTED_MAX_PATH + 2) * sizeof(WCHAR) ) ;
		auto sz = firstFile.getPointer<LPWSTR>();

		::DragQueryFileW( hdrop.getPointer<HDROP>(), 0, sz, EXTENTED_MAX_PATH ) ;
		filename = sz ;
	}
	catch ( const lib::exception& ex )
	{
		auto err = lib::sprintf( L"EXCEPTION\n", ex.what() ) ;
		err.debug() ;
		return HR_ABORT ;
	}
	catch( const std::exception& ex ) 
	{
		auto err = lib::sprintf( L"EXCEPTION\n", ex.what() ) ;
		err.debug() ;
		return HR_ABORT ;
	}
	catch( ... ) 
	{
		auto err = lib::sprintf( L"EXCEPTION\n..." ) ;
		err.debug() ;
		return HR_ABORT ;
	}

	//ALBY dll exe chack

	msg = lib::sprintf( L"[", filename, L"]" ) ;
	msg.debug();

	return E_NOTIMPL ; //ALBY change to S_OK
}

STDMETHODIMP
assemblyShelllPropertyPage::AddPages
(
	LPFNSVADDPROPSHEETPAGE pfnAddPage,
	LPARAM lParam
)
{
	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [AddPages]");
	msg.debug();

	return E_NOTIMPL;
}

STDMETHODIMP
assemblyShelllPropertyPage::ReplacePage
(
	EXPPS uPageID,
	LPFNSVADDPROPSHEETPAGE pfnReplaceWith,
	LPARAM lParam
) 
{
	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [ReplacePage]");
	msg.debug();

	return E_NOTIMPL;
}


