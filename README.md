# alby.assemblyShellExtension FAQ

# what is it?

an extension to windows explorer to let you see .net assembly attributes in the file properties dialog


# how do i build it?

visual studio 2013

    msbuild alby.assemblyShellExtension.sln /t:Clean,Rebuild /p:Configuration=Release /p:Platform=x64


# what are the key artifacts?

    bin\alby.assemblyShellExtension.dll 
    (C++ ATL COM shell extension dll, this is the money shot)


    bin\alby.assemblyAttributes.exe 

(.net dll that reflects other .net assemblies, provides attribute information to C++ dll above)

    bin\alby.assemblyAttributes.exe.config

(required config file for above)


# any other artifacts?

- a C++ test program

    bin\alby.testAssemblyAttributes.exe 

# what's the bitness?

- all binaries produced are 64 bit only. *I don't do 32 bit, it's 2016 FFS.*

--*I don't do 32 bit, it's 2016 FFS*


# how do i install it?

TO DO check path stuff

put the following files 

    bin\alby.assemblyAttributes.exe
    bin\alby.assemblyAttributes.exe.config
    bin\alby.assemblyShellExtension.dll 

into the same folder 

then run as admin

    regsvr32 alby.assemblyShellExtension.dll


# how do i uninstall it?

run as admin

    regsvr32 /u alby.assemblyShellExtension.dll


# how do i run it?

you don't run it.

right click on a .net .exe or .dll in windows explorer, click properties, click on the new tab titled "TO DO xxx assembly attributes"


TO DO picture

# what's an example of running the test program?

    bin\alby.testAssemblyAttributes.exe "bin\alby.assemblyAttributes.exe" "C:\Program Files\Microsoft Visual Studio 12.0\Common7\IDE\Xml\Microsoft.XslDebugger.dll"


# what was this developed and tested on?

- visual studio 2013
- window 8
- not tested on any other windows operating system, so *caveat emptor*

# what's the licence ?

- [the MIT licence](https://opensource.org/licenses/MIT)


# alby's best bet on wide character set usage in C++ on windows

- always use windows win32/win64 unicode xxxW functions wherever possible, ie avoid xxxA ansi functions 
- always use std::wstring internally
- always use std::string externally, ie when piping to std::cout, file io, pipe io, etc
- always pipe to std::cout
- never ever pipe to std::wcout
- repeat: never ever pipe unicode/utf16 std::wstrings to any io. instead, convert to utf8 std::strings and pipe to std::cout


