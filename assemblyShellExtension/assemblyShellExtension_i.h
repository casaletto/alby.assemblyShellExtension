

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Feb 12 12:11:56 2016
 */
/* Compiler settings for assemblyShellExtension.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __assemblyShellExtension_i_h__
#define __assemblyShellExtension_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IassemblyShelllPropertyPage_FWD_DEFINED__
#define __IassemblyShelllPropertyPage_FWD_DEFINED__
typedef interface IassemblyShelllPropertyPage IassemblyShelllPropertyPage;

#endif 	/* __IassemblyShelllPropertyPage_FWD_DEFINED__ */


#ifndef __assemblyShelllPropertyPage_FWD_DEFINED__
#define __assemblyShelllPropertyPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class assemblyShelllPropertyPage assemblyShelllPropertyPage;
#else
typedef struct assemblyShelllPropertyPage assemblyShelllPropertyPage;
#endif /* __cplusplus */

#endif 	/* __assemblyShelllPropertyPage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IassemblyShelllPropertyPage_INTERFACE_DEFINED__
#define __IassemblyShelllPropertyPage_INTERFACE_DEFINED__

/* interface IassemblyShelllPropertyPage */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IassemblyShelllPropertyPage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5699F9C4-8A04-45EF-8B24-F1E6A636E194")
    IassemblyShelllPropertyPage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HelloWorld( 
            BSTR aString,
            /* [retval][out] */ BSTR *returnedBStr) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IassemblyShelllPropertyPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IassemblyShelllPropertyPage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IassemblyShelllPropertyPage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IassemblyShelllPropertyPage * This);
        
        HRESULT ( STDMETHODCALLTYPE *HelloWorld )( 
            IassemblyShelllPropertyPage * This,
            BSTR aString,
            /* [retval][out] */ BSTR *returnedBStr);
        
        END_INTERFACE
    } IassemblyShelllPropertyPageVtbl;

    interface IassemblyShelllPropertyPage
    {
        CONST_VTBL struct IassemblyShelllPropertyPageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IassemblyShelllPropertyPage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IassemblyShelllPropertyPage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IassemblyShelllPropertyPage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IassemblyShelllPropertyPage_HelloWorld(This,aString,returnedBStr)	\
    ( (This)->lpVtbl -> HelloWorld(This,aString,returnedBStr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IassemblyShelllPropertyPage_INTERFACE_DEFINED__ */



#ifndef __assemblyShellExtensionLib_LIBRARY_DEFINED__
#define __assemblyShellExtensionLib_LIBRARY_DEFINED__

/* library assemblyShellExtensionLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_assemblyShellExtensionLib;

EXTERN_C const CLSID CLSID_assemblyShelllPropertyPage;

#ifdef __cplusplus

class DECLSPEC_UUID("382E162B-4E2A-4F49-B120-64070B2F6084")
assemblyShelllPropertyPage;
#endif
#endif /* __assemblyShellExtensionLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


