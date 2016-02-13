#pragma once

namespace alby
{
	namespace assemblyAttributes
	{
		namespace lib
		{
			class globalLock
			{
				protected:
					HGLOBAL _handle  = NULL ;
					LPVOID  _pointer = NULL ;

				public:
					globalLock( HGLOBAL h ) ;
					virtual ~globalLock() ;

					template <typename T>
					T getPointer()
					{
						return (T) this->_pointer ;
					}
			};

		} // ns lib

	} // ns assemblyAttributes

} //  ns alby

