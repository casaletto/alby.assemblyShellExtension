#pragma once

namespace alby
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

			static std::wstring stringHelper::rtrim(const std::wstring& wstr);
			static std::wstring stringHelper::ltrim(const std::wstring& wstr);
			static std::wstring stringHelper::trim(const std::wstring& wstr);

	} ;

}