#pragma once

namespace alby
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
}

