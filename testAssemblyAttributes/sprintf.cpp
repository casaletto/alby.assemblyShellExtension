#include "stdafx.h"
#include "stringhelper.h" 
#include "exception.h" 
#include "sprintf.h"

using namespace alby ;

//ALBY remove me

/*
sprintf::sprintf()
{
}


sprintf::~sprintf()
{
}


std::wstring sprintf::toWstring()
{
	return ss_.rdbuf()->str();
}


std::string sprintf::toString()
{
	return alby::stringhelper::w2s( this->toWstring() );
}
*/

/*
template<typename ... T>
sprintf::sprintf( const T& ... head )
{
	this->stream( head ... ) ;
}
*/

/*
template<typename U, typename ... T>
sprintf::sprintf(const U& head, const T& ... tail)
{

	this->stream(head, tail ...); // recursion !
}
*/

/*
// specialisations
template<typename ... T>
sprintf::sprintf( const std::wstring& head, const T& ... tail )
{
	//this->stream( alby::stringhelper::toWstring(head), tail ... ) ;
	this->stream( head, tail ... ) ;
}
*/

/*
template<typename ... T>
sprintf::sprintf(const char* head, const T& ... tail)
{
	this->stream(alby::stringhelper::toWstring(head), tail ...);
}
*/


// protected

/*
void sprintf::stream()
{
}

template<typename U, typename ... T>
void sprintf::stream( const U& head, const T& ... tail )
{
	this->ss_ << head ;

	this->stream( tail ... ) ; // recursion !
}
*/

// specialisations

/*
template<typename ... T>
void sprintf::stream( const std::wstring& head, const T& ... tail )
{
	//this->stream( alby::stringhelper::toWstring( head ), tail ... ) ;
	this->stream( head, tail ... ) ;
}
*/

/*
template<typename ... T>
void sprintf::stream(const std::string& head, const T& ... tail )
{
	this->stream(alby::stringhelper::toWstring( head ), tail ... ) ;
}
*/

/*
template<typename ... T>
void sprintf::stream( const char* head, const T& ... tail )
{
	this->stream( alby::stringhelper::toWstring( head ), tail ... ) ;
}
*/



