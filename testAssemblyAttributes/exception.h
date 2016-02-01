#pragma once

namespace alby
{
	namespace assemblyAttributes
	{
		namespace lib
		{
			class exception
			{
				protected:
					static const int BUFFER_SIZE = 500 ;

					std::wstring _message ;

					std::wstring getLastError() ;

				public:
					virtual ~exception() throw() ;
					exception() throw() ;

					exception( const std::wstring& message ) throw() ;
					exception( const std::wstring& message, const char* file, int line ) throw() ;
			
					exception( const exception& ) throw() ;
					exception& operator=( const exception& ) throw() ;

					virtual std::wstring what() const throw() ;
			} ;

		} // ns lib

	} // ns assemblyAttributes

} //  ns alby

