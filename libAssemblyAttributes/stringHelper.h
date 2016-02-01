#pragma once

namespace alby
{
	namespace assemblyAttributes
	{
		namespace lib
		{
			class stringHelper
			{
				protected:
					const static std::wstring __delimiters ;

				public:

					stringHelper();
					virtual ~stringHelper();

					static std::wstring stringHelper::s2ws( const std::string&  str  ) ;
					static std::string  stringHelper::ws2s( const std::wstring& wstr ) ;

					static std::wstring stringHelper::rtrim( const std::wstring& wstr ) ;
					static std::wstring stringHelper::ltrim( const std::wstring& wstr ) ;
					static std::wstring stringHelper::trim ( const std::wstring& wstr ) ;

					static std::vector<std::wstring> stringHelper::split( const std::wstring& wstr, wchar_t delimiter ) ;
			} ;

		} // ns lib

	} // ns assemblyAttributes

} //  ns alby

