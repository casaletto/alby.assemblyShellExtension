#include "stdafx.h"
#include "stringHelper.h" 
#include "exception.h" 
#include "sprintf.h"
#include "handle.h"
#include "process.h"
#include "helper.h"

using namespace alby ;

process::process()
{
}

process::~process()
{
}

std::wstring process::getStdout()
{
	return this->_stdout ;
}

std::wstring process::getStderr()
{
	return this->_stderr ;
}

void process::setStdout( const std::wstring& str )
{
	this->_stdout = str ;
}

void process::setStderr( const std::wstring& str)
{
	this->_stderr = str ;
}

int process::exec( const std::wstring& exe, const std::wstring& parameter ) 
{
	this->setStdout( std::wstring() ) ;
	this->setStderr( std::wstring() ) ;
 
	if ( exe.size() == 0 )
		throw alby::exception( L"No executable file was passed in.", __FILE__, __LINE__ ) ;

	if ( parameter.size() == 0)
		throw alby::exception( L"No parameter was passed in.",  __FILE__, __LINE__ ) ;

	// format command line with quotes "exe" "param"
	auto q = L"\"" ;
	auto cmdline = alby::sprintf( q, exe, q, L" ", q, parameter, q ) ;
	cmdline.debug() ;

	// create the pipes
	HANDLE hChildStdoutRead  ;
	HANDLE hChildStdoutWrite ;

	HANDLE hChildStderrRead;
	HANDLE hChildStderrWrite;

	::SECURITY_ATTRIBUTES sa ;
	::ZeroMemory( &sa, sizeof(sa) ) ;
	sa.nLength = sizeof(sa) ;
	sa.bInheritHandle = TRUE ;

	// stdout
	auto b = ::CreatePipe( &hChildStdoutRead, &hChildStdoutWrite, &sa, 0 ) ;
	if ( b == 0 )
		throw alby::exception( L"CreatePipe() failed.", __FILE__, __LINE__ );

	// safe handle cleanup
	alby::handle handleChildStdoutRead ( hChildStdoutRead  ) ;
	alby::handle handleChildStdoutWrite( hChildStdoutWrite ) ;

	b = ::SetHandleInformation( hChildStdoutRead, HANDLE_FLAG_INHERIT, 0 ) ;
	if ( b == 0 )
		throw alby::exception( L"SetHandleInformation() failed.", __FILE__, __LINE__ ) ;

	// stderr
	b = ::CreatePipe( &hChildStderrRead, &hChildStderrWrite, &sa, 0 ) ;
	if ( b == 0 )
		throw alby::exception( L"CreatePipe() failed.", __FILE__, __LINE__ );

	// safe handle cleanup
	alby::handle handleChildStderrRead ( hChildStderrRead  ) ;
	alby::handle handleChildStderrWrite( hChildStderrWrite ) ;

	b = ::SetHandleInformation( hChildStderrRead, HANDLE_FLAG_INHERIT, 0 ) ;
	if ( b == 0 )
		throw alby::exception( L"SetHandleInformation() failed.", __FILE__, __LINE__ ) ;

	// fire child process
	STARTUPINFO si;
	::ZeroMemory( &si, sizeof(si) ) ;

	PROCESS_INFORMATION pi;
	::ZeroMemory( &pi, sizeof(pi) ) ;

	si.cb = sizeof(si) ;
	si.dwFlags |= STARTF_USESTDHANDLES ; 

	si.hStdOutput = hChildStdoutWrite;
	si.hStdError = hChildStderrWrite ; 

	b = ::CreateProcessW
	(
		NULL,
		(LPWSTR) cmdline.ws().c_str() ,     
		NULL,
		NULL,
		TRUE, // inherit handles
		0, 
		NULL,
		NULL,
		&si,
		&pi
	) ;

	if ( b == 0 )
		throw alby::exception( L"CreateProcessW() failed.", __FILE__, __LINE__ ) ; 

	// safe handle cleanup
	alby::handle handleProcess( pi.hProcess ) ;
	alby::handle handleThread( pi.hThread ) ;

	// now we have to close child's write handles !
	handleChildStdoutWrite.close();
	handleChildStderrWrite.close();

	::WaitForInputIdle( pi.hProcess, INFINITE ) ;

	// get the child's outputs
	std::string strStdout ;
	std::string strStderr ;

	this->getProcessOutput( hChildStdoutRead, hChildStderrRead, strStdout, strStderr ) ;

	this->setStdout( stringHelper::s2ws( strStdout ) ) ;
	this->setStderr( stringHelper::s2ws( strStderr ) ) ;

	// wait for child process exit
	DWORD rc = 1 ;
	::WaitForSingleObject(pi.hProcess, INFINITE);
	::GetExitCodeProcess( pi.hProcess, &rc ) ;

	return rc ;
}

void process::getProcessOutput
( 
	HANDLE hStdout, 
	HANDLE hStderr, 
	std::string& strStdout,
	std::string& strStderr
)
{
	std::vector<BYTE> stdoutBytes ;
	std::vector<BYTE> stderrBytes ;

	DWORD stdoutBytesRead ;
	DWORD stderrBytesRead ;

	BYTE buffer[ BUFFER_SIZE+10 ] ;

	bool stdoutEOF = false ;
	bool stderrEOF = false ; 

	for ( ;; )
	{
		// stdout
		if ( ! stdoutEOF )
		{
			::ZeroMemory( buffer, sizeof(buffer) ) ;

			stdoutBytesRead = 0 ;
			::ReadFile( hStdout, buffer, BUFFER_SIZE, &stdoutBytesRead, NULL ) ;

			if ( stdoutBytesRead > 0 )
				 std::copy( buffer, buffer + stdoutBytesRead, std::back_inserter(stdoutBytes) ) ; // append to byte array
			else
				stdoutEOF = true ;
		}

		// stderr
		if ( ! stderrEOF )
		{
			::ZeroMemory( buffer, sizeof(buffer) ) ;

			stderrBytesRead = 0 ;
			::ReadFile( hStderr, buffer, BUFFER_SIZE, &stderrBytesRead, NULL ) ;

			if ( stderrBytesRead > 0 )
				std::copy( buffer, buffer + stderrBytesRead, std::back_inserter(stderrBytes) ) ; // append to byte array
			else
				stderrEOF = true;
		}

		if ( stdoutEOF && stderrEOF ) break ;
	}

	stdoutBytes.push_back( 0 ) ;  // terminate C string
	stdoutBytes.push_back( 0 ) ;

	stderrBytes.push_back( 0 ) ; 
	stderrBytes.push_back( 0 ) ;

	strStdout = std::string( (char*) stdoutBytes.data() ) ;
	strStderr = std::string( (char*) stderrBytes.data() ) ;
}


