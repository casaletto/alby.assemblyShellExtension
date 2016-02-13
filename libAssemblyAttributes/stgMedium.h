#pragma once

namespace alby
{
	namespace assemblyAttributes
	{
		namespace lib
		{
			class stgMedium
			{
				public:
					stgMedium( IDataObject *pDataObject, FORMATETC& formatEtc ) ;
					virtual ~stgMedium() ;

					STGMEDIUM getStgMedium() ;

				protected:
					STGMEDIUM	_stgMedium ;
					bool		_ok = false ;
			} ;

		} // ns lib

	} // ns assemblyAttributes

} //  ns alby

