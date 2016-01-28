#pragma once

namespace alby
{
	class helper
	{
		public:

			helper();
			virtual ~helper();

			static std::vector<std::wstring> helper::argvToVector( int argc, wchar_t* argv[] ) ;

			static void getArguments( std::vector<std::wstring>& args, std::wstring& inspector, std::wstring& inspectee ) ;
	};

}
