#pragma once

namespace alby
{
	namespace assemblyAttributes
	{
		namespace lib
		{
			class globalAlloc
			{
				protected:
					SIZE_T	_bytes = 0 ;
					HGLOBAL	_handle = NULL ;

				public:
					globalAlloc( SIZE_T bytes ) ;
					virtual ~globalAlloc() ;

					template <typename T>
					T getHandle()
					{
						return (T) this->_handle;
					}

					template <typename T>
					T getPointer()
					{
						return (T) this->_handle;
					}

			};

		} // ns lib

	} // ns assemblyAttributes

} //  ns alby

