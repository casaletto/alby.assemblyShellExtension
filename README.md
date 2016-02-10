# alby.assemblyShellExtension FAQ

# what is it?

a tool to let you see your .net assembly attributes in windows explorer's file properties dialog


# how do i build it?

visual studio 2013:

msbuild alby.assemblyShellExtension.sln /t:Clean,Rebuild /p:Configuration=Release /p:Platform=x64


# what are the key artifacts?

bin\alby.assemblyAttributes.exe

bin\alby.assemblyAttributes.exe.config

bin\alby.assemblyShellExtension.dll (the money shot)


# any other artifacts?

bin\alby.testAssemblyAttributes.exe (a test program)


# how do i install it?

TO DO
put the following files 

bin\alby.assemblyAttributes.exe

bin\alby.assemblyAttributes.exe.config

bin\alby.assemblyShellExtension.dll 

in the same folder. 
then run

regsvr32 alby.assemblyShellExtension.dll


# how do i uninstall it?

regsvr32 /u alby.assemblyShellExtension.dll


# how do i run it?

TO DO right-click on a .net .exe or .dll in windows explorer, and select properties.




# what's an example of running the test program?

bin\alby.testAssemblyAttributes.exe bin\alby.assemblyAttributes.exe c:\Windows\Microsoft.NET\Framework\v4.0.30319\Microsoft.Activities.Build.dll

bin\alby.testAssemblyAttributes.exe "bin\alby.assemblyAttributes.exe" "C:\Program Files\Microsoft Visual Studio 12.0\Common7\IDE\Xml\Microsoft.XslDebugger.dll"


# what was this developed and tested on?

visual studio 2013

window 8


# alby's c++ wide character best bet

- use windows xxxW functions wherever possible 
- use std::wstring internally
- use std::string  externally, ie cout, file io
- repeat: never ever send utf16 wstring's to io, only ever send utf8 string's


