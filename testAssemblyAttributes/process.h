#pragma once

namespace alby
{
	class process
	{
		protected:
			static const int BUFFER_SIZE = 50 ;

			std::wstring _stdout ;
			std::wstring _stderr ;

			void setStdout( const std::wstring& ) ;
			void setStderr( const std::wstring& ) ;

			void getProcessOutput( HANDLE hStdout, HANDLE hStderr, std::string& strStdout, std::string& strStderr ) ;

		public:
			process() ;
			virtual ~process() ;

			int exec( const std::wstring& exe, const std::wstring& parameter ) ;

			std::wstring getStdout() ;
			std::wstring getStderr() ;
	};
}


