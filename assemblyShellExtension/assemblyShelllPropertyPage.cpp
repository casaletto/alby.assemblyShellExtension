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
#include "dllmain.h"
#include "assemblyShelllPropertyPage.h"

using namespace ATL ; 

namespace lib = alby::assemblyAttributes::lib;

assemblyShelllPropertyPage::assemblyShelllPropertyPage()
{
	//auto msg = lib::sprintf(L"assemblyShelllPropertyPage [constructor]");
	//msg.debug();
}

HRESULT 
assemblyShelllPropertyPage::FinalConstruct()
{
	auto msg = lib::sprintf( L"assemblyShelllPropertyPage [final constructor]" ) ;
	msg.debug() ;

	msg = lib::sprintf( L"assemblyShelllPropertyPage _WIN32_WINNT=0x", 
						std::setw(4), 
						std::setfill( (WCHAR) '0' ), 
						std::hex, 
						_WIN32_WINNT ) ;
	msg.debug() ;

	msg = lib::sprintf( L"assemblyShelllPropertyPage WINVER=0x", 
						std::setw(4),
						std::setfill( (WCHAR) '0' ),
						std::hex,
						WINVER ) ; 
	msg.debug() ;

	return S_OK ;
}

void 
assemblyShelllPropertyPage::FinalRelease()
{
	auto msg = lib::sprintf( L"assemblyShelllPropertyPage [final release]" ) ;
	msg.debug() ;
}

STDMETHODIMP 
assemblyShelllPropertyPage::HelloWorld( BSTR aString, BSTR* returnedBStr)
{
	auto msg = lib::sprintf( L"assemblyShelllPropertyPage [HelloWorld]" ) ;
	msg.debug() ;

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
	this->_dic.clear() ;

	const HRESULT HR_ABORT = E_INVALIDARG ;

	FORMATETC formatetc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL } ;

	std::wstring filename ;

	auto msg = lib::sprintf( L"assemblyShelllPropertyPage [Initialize]" ) ;
	msg.debug() ;

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

		//ALBY auto directory = lib::helper::getDirectoryFromPath( filename ) ;

		// file name suffix must in [ .dll .exe ]
		auto ok = lib::stringHelper::endsWith( filename, L".dll", false ) ||
				  lib::stringHelper::endsWith( filename, L".exe", false ) ;

		if ( ! ok ) return HR_ABORT ;

		// get current folder to find exe path
		auto folder = lib::helper::getCurrentModuleDirectory() ;
		auto exe64  = lib::sprintf( folder, L"\\", lib::helper::CSHARP_ASSEMBLY_ATTRIBUTES_EXE_64 ) ; 
		auto exe32  = lib::sprintf( folder, L"\\", lib::helper::CSHARP_ASSEMBLY_ATTRIBUTES_EXE_32 ) ; 

		// call the child .net process, 64 bit version
		lib::process pr64 ;
		auto rc = pr64.exec( exe64.ws(), L"", filename ) ;

		auto theStdout = lib::stringHelper::trim( pr64.getStdout() ) ;
		auto theStderr = lib::stringHelper::trim( pr64.getStderr() ) ;

		msg = lib::sprintf( L"rc 64 [", rc, L"]" ) ;
		msg.debug();

		// may have failed due to bad bitness
		auto badImageException = ( rc != 0 ) && lib::stringHelper::contains( theStderr, L"System.BadImageFormatException" ) ;

		// call the child .net process, 32 bit version
		if ( badImageException )
		{
			lib::process pr32 ;
			rc = pr32.exec( exe32.ws(), L"", filename ) ;

			theStdout = lib::stringHelper::trim( pr32.getStdout() ) ;
			theStderr = lib::stringHelper::trim( pr32.getStderr() ) ;

			msg = lib::sprintf( L"rc 32 [", rc, L"]" ) ;
			msg.debug() ;
		}

		if ( ! theStderr.empty()  )
			  throw lib::exception( theStderr, __FILE__, __LINE__);

		if ( rc != 0 ) return HR_ABORT ;

		// transform the flat string to a dictionary
		this->_dic = lib::helper::toMap( theStdout, L'\n', L'|' ) ;

		// dump it
		for ( auto k : this->_dic )
			  lib::sprintf( L"#", k.first, L"# = [", k.second, L"]" ).debug() ;

		// transform the dic to a formatted string for ui display
		this->_uiString = lib::helper::mapToString( this->_dic ) ;
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

	return S_OK ; 
}

STDMETHODIMP
assemblyShelllPropertyPage::AddPages
(
	LPFNSVADDPROPSHEETPAGE pfnAddPage,
	LPARAM lParam
)
{
	const HRESULT HR_ABORT = E_NOTIMPL ;

	auto msg = lib::sprintf(L"assemblyShelllPropertyPage [AddPages]");
	msg.debug();

	try
	{
		auto mystr = new std::wstring( this->_uiString ) ; // freed by the receiver, the dlg proc

		PROPSHEETPAGEW psp ;
		::ZeroMemory( &psp, sizeof(psp) ) ;
		
		psp.dwSize		= sizeof( PROPSHEETPAGEW ) ;
		psp.dwFlags		= PSP_USEREFPARENT | PSP_USETITLE | PSP_USEICONID ;
		psp.hInstance	= _AtlBaseModule.m_hInst ; 
		psp.pszTemplate = MAKEINTRESOURCEW( IDD_PROPPAGE_LARGE ) ;
		psp.pszIcon		= MAKEINTRESOURCEW( IDI_ICON1 )  ;
		psp.pszTitle	= L"alby.NET" ;
		psp.pfnDlgProc	= (DLGPROC) MyDlgProc  ;
		psp.lParam		= (LPARAM) mystr ; 
		//psp.pfnCallback = PropPageCallbackProc;
		psp.pcRefParent = (UINT*) &_AtlModule.m_nLockCnt ;

		auto hPage = ::CreatePropertySheetPageW( &psp ) ;
		if ( hPage != NULL )
			 if ( ! pfnAddPage( hPage, lParam ) )
			 {
				::DestroyPropertySheetPage( hPage ) ;
				return HR_ABORT ; 
			 }

		return S_OK ;		
	}
	catch ( const lib::exception& ex )
	{
		auto err = lib::sprintf( L"EXCEPTION\n", ex.what() ) ;
		err.debug() ;
		return HR_ABORT ;
	}
	catch ( const std::exception& ex )
	{
		auto err = lib::sprintf( L"EXCEPTION\n", ex.what() ) ;
		err.debug();
		return HR_ABORT ;
	}
	catch (...)
	{
		auto err = lib::sprintf( L"EXCEPTION\n..." ) ;
		err.debug() ;
		return HR_ABORT ;
	}

	return HR_ABORT ; 
}

BOOL CALLBACK 
assemblyShelllPropertyPage::MyDlgProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	BOOL rc = FALSE ;

	switch( msg )
	{
		case WM_INITDIALOG:
		{ 
			auto p = (PROPSHEETPAGEW*) lParam ;
			::SetWindowLong( hwnd, GWLP_USERDATA, (LONG) p->lParam ) ;

			auto pstr = (std::wstring*) p->lParam ;
			std::wstring str( *pstr ) ;
			delete pstr ;

			::SetDlgItemTextW( hwnd, IDC_EDIT1, str.c_str() ) ; 
			return TRUE ;
		}

		case WM_NOTIFY:
		{
			/*
			auto phdr = (NMHDR*) lParam ;
			switch( phdr->code )
			{
				default: break ;
			}
			*/			
			break ;
		}

		case WM_COMMAND: 
		{			
			switch( LOWORD(wParam) )
			{
				case IDC_EDIT1:
					::SendDlgItemMessage( hwnd, IDC_EDIT1, EM_SETSEL, -1, -1 ) ;
					return 0 ;

				break ;
			}
			break;
		}

		default: break ;
	}

	return rc ;
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


