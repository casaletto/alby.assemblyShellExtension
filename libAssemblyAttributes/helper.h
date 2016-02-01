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

					helper();
					virtual ~helper();

					static std::vector<std::wstring> helper::argvToVector( int argc, wchar_t* argv[] ) ;

					static void getArguments( std::vector<std::wstring>& args, std::wstring& inspector, std::wstring& inspectee ) ;

					static std::map<std::wstring, std::wstring> toMap( const std::wstring, wchar_t majorDelim, wchar_t minorDelim ) ;
			} ;
		
		} // ns lib

	} // ns assemblyAttributes

} //  ns alby


