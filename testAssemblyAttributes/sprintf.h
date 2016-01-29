#pragma once

namespace alby
{
	class sprintf
	{
		protected:
			std::wstringstream _ss ;

		public:
			sprintf()
			{
			}

			virtual ~sprintf()
			{
			}

			sprintf::sprintf( const sprintf& rhs ) 
			{
				_ss = std::wstringstream() ;
				this->_ss << rhs._ss.str() ;
			}

			sprintf& sprintf::operator=( const sprintf& rhs ) 
			{
				_ss = std::wstringstream();
				this->_ss << rhs._ss.str();

				return *this;
			}

			std::wstring wstring()
			{
				return _ss.rdbuf()->str() ;
			}

			template<typename U, typename ... T>
			sprintf( const U& head, const T& ... tail )
			{
				stream( head, tail ... ) ;
			}

			void stdoutput()
			{
				auto str = alby::stringHelper::ws2s( this->wstring() ) ;
				std::cout << str << std::endl ;
			}

			void stderror()
			{
				auto str = alby::stringHelper::ws2s(this->wstring());
				std::cerr << str << std::endl;
			}

			void debug()
			{
				::OutputDebugStringW( this->wstring().c_str() );
			}

		protected:

			void stream()
			{
			}

			template<typename U, typename ... T>
			void stream( const U& head, const T& ... tail ) 
			{
				_ss << head ;

				stream( tail ... ) ;
			}

	};
}

