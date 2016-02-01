#pragma once

namespace alby
{
	namespace assemblyAttributes
	{
		namespace lib
		{
			class handle
			{
				protected:
					HANDLE _handle ;
					bool _set ;

				public:
					handle() ;
					handle( HANDLE h ) ;
					virtual ~handle() ;

					HANDLE  getHandle() ;
					bool isSet();
					void close() ;
			};

		} // ns lib

	} // ns assemblyAttributes

} //  ns alby

