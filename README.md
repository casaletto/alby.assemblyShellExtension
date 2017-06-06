# alby.assemblyShellExtension FAQ

# what is it?

an extension to windows explorer to let you see .net assembly attributes in the file properties dialog


# how do i build it?

visual studio 2013

    msbuild alby.assemblyShellExtension.sln /t:Clean,Rebuild /p:Configuration=Release /p:Platform=x64


# what are the key artifacts ?

a C++ ATL COM windows explorer shell extension dll

    bin\alby.assemblyShellExtension.dll 

	
a C#.net dll that reflects other .net assemblies, provides attribute information to the dll above (and a 32 bit version for loading x86 processor architecture assemblies)

    bin\alby.assemblyAttributes.exe 
    bin\alby.assemblyAttributes32.exe 


and the required configuration files for the above C# dlls

    bin\alby.assemblyAttributes.exe.config
    bin\alby.assemblyAttributes32.exe.config


# any other artifacts ?

a C++ test program

    bin\alby.testAssemblyAttributes.exe 

	
# how do i install it ?

put the following files 

    bin\alby.assemblyAttributes.exe
    bin\alby.assemblyAttributes.exe.config
    bin\alby.assemblyAttributes32.exe
    bin\alby.assemblyAttributes32.exe.config
	bin\alby.assemblyShellExtension.dll 

into the same folder 

then run as admin

    regsvr32 bin\alby.assemblyShellExtension.dll


# how do i uninstall it ?

run as admin

    regsvr32 /u bin\alby.assemblyShellExtension.dll


# how do i run it ?

you don't run it, it's a plug in to explorer

- right click on a .net .exe or .dll in windows explorer
- click properties
- click on the tab titled alby.NET


# what does it look like?

![here's what it looks like](https://raw.githubusercontent.com/casaletto/alby.assemblyShellExtension/master/doc/theFinishedProduct.png)


# what's an example of running the test program?

    bin\alby.testAssemblyAttributes.exe "bin\alby.assemblyAttributes.exe" "C:\Program Files\Microsoft Visual Studio 12.0\Common7\IDE\Xml\Microsoft.XslDebugger.dll"


# what was this developed and tested on?

- visual studio 2013
- windows 8.1 version 6.3.9600
- windows server 2012 r2 version 6.3.9600
- not tested on any other windows operating system, so *caveat emptor*

# what's the licence ?

- [the MIT licence](https://opensource.org/licenses/MIT)


# bibliography

the following links were very helpful in learning how to write this windows shell extension

- https://msdn.microsoft.com/en-us/library/windows/desktop/ms682499.aspx	
- https://msdn.microsoft.com/en-us/library/windows/desktop/cc144067.aspx
- https://msdn.microsoft.com/en-us/library/windows/desktop/cc144106.aspx
- https://msdn.microsoft.com/en-us/library/windows/desktop/hh127448.aspx
- http://www.codeproject.com/Articles/441/The-Complete-Idiot-s-Guide-to-Writing-Shell-Extens
- http://www.codeproject.com/Articles/463/The-Complete-Idiots-Guide-to-Writing-Shell-Exten
- https://msdn.microsoft.com/en-us/library/windows/desktop/bb774548.aspx
- https://powerext.codeplex.com


# alby's best bet on wide character set usage in C++ on windows

- always use windows win32/win64 unicode xxxW functions wherever possible, ie avoid xxxA ansi functions 
- always use std::wstring internally
- always use std::string externally, ie when piping to std::cout, file io, pipe io, etc
- always pipe to std::cout
- never ever pipe to std::wcout
- repeat: never ever pipe unicode/utf16 std::wstrings to any io. instead, convert to utf8 std::strings and pipe to std::cout


