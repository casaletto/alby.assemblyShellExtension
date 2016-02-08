#pragma once

#include "resource.h"       
#include "assemblyShellExtension_i.h"

using namespace ATL ;

class ATL_NO_VTABLE assemblyShelllPropertyPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<assemblyShelllPropertyPage, &CLSID_assemblyShelllPropertyPage>,
	public IassemblyShelllPropertyPage
{

public:
	assemblyShelllPropertyPage() ;

DECLARE_REGISTRY_RESOURCEID(IDR_ASSEMBLYSHELLLPROPERTYPAGE)
DECLARE_NOT_AGGREGATABLE(assemblyShelllPropertyPage)

BEGIN_COM_MAP(assemblyShelllPropertyPage)
	COM_INTERFACE_ENTRY(IassemblyShelllPropertyPage)
END_COM_MAP()

DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() ;
	void FinalRelease() ;

	STDMETHOD(HelloWorld)(BSTR aString, BSTR* returnedBStr);
};

OBJECT_ENTRY_AUTO(__uuidof(assemblyShelllPropertyPage), assemblyShelllPropertyPage)

