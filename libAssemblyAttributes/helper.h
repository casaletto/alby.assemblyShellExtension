#pragma once

namespace alby
{
	namespace assemblyAttributes
	{
		namespace lib
		{
			class helper
			{
				public:
					static const std::wstring CSHARP_ASSEMBLY_ATTRIBUTES_EXE ; 
					static const int EXTENTED_MAX_PATH = 32767 ;

					helper();
					virtual ~helper();

					static std::vector<std::wstring> 
					helper::argvToVector( int argc, wchar_t* argv[] ) ;

					static void 
					getArguments( std::vector<std::wstring>& args, std::wstring& inspector, std::wstring& inspectee ) ;

					static std::map<std::wstring, std::wstring> 
					toMap( const std::wstring, wchar_t majorDelim, wchar_t minorDelim ) ;

					static std::wstring 
					getDateTime() ;

					static std::wstring 
					getCurrentModuleDirectory() ;

					static std::vector<std::wstring>
					getLoadedModules( HANDLE hProcess ) ;
			} ;
		
		} // ns lib

	} // ns assemblyAttributes

} //  ns alby


