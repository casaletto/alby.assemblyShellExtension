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

		auto firstFile = lib::globalAlloc( (lib::helper::EXTENTED_MAX_PATH + 2) * sizeof(WCHAR) ) ;
		auto sz = firstFile.getPointer<LPWSTR>();

		// get file name from shell
		::DragQueryFileW( hdrop.getPointer<HDROP>(), 0, sz, lib::helper::EXTENTED_MAX_PATH ) ;
		filename = sz ;

		// file name suffix must in [ .dll .exe ]
		auto ok = lib::stringHelper::endsWith( filename, L".dll", false ) ||
				  lib::stringHelper::endsWith( filename, L".exe", false ) ;

		if ( ! ok ) return HR_ABORT ;

		// get current folder to find exe path
		auto folder = lib::helper::getCurrentModuleDirectory() ;
		auto exe    = lib::sprintf( folder, L"\\", lib::helper::CSHARP_ASSEMBLY_ATTRIBUTES_EXE ) ; 

		// call the child .net process
		lib::process pr ;
		auto rc = pr.exec( exe.ws(), filename ) ;

		auto theStdout = lib::stringHelper::trim( pr.getStdout() ) ;
		auto theStderr = lib::stringHelper::trim( pr.getStderr() ) ;

		msg = lib::sprintf( L"rc [", rc, L"]" ) ;
		msg.debug();

		msg = lib::sprintf( L"stdout [\n", theStdout, L"]");
		msg.debug();

		msg = lib::sprintf( L"stderr [\n", theStderr, L"]");
		msg.debug();

		if ( theStderr.size() > 0 ) return HR_ABORT ;
		if ( rc !=  0             ) return HR_ABORT ;

		//ALBY here



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

	return E_NOTIMPL ; //ALBY TO DO at the end:change to S_OK
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


