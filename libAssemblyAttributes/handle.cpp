#include "stdafx.h"
#include "stringHelper.h"
#include "exception.h" 
#include "handle.h"

using namespace alby::assemblyAttributes::lib ;

handle::handle()
{
	this->_set = false ;
}

handle::handle( HANDLE h )
{
	this->_handle = h;
	this->_set = true;
}

handle::~handle()
{
	this->close() ;
}

void handle::close()
{
	if ( ! this->isSet() ) return ;

	::CloseHandle( getHandle() ) ;

	this->_set = false ;
}

HANDLE handle::getHandle()
{
	return this->_handle ;
}

bool handle::isSet()
{
	return this->_set ;
}

