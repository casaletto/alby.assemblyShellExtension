# alby.assemblyShellExtension FAQ

# what is it?

a tool to let you see your .net assembly attributes in windows explorer's file properties dialog


# how do i build it?

visual studio 2013:

msbuild alby.assemblyShellExtension.sln /t:Clean,Rebuild /p:Configuration=Release /p:Platform=x64



# how do i install and run it?

TO DO

# how do i run it?

TO DO

# how do i uninstall it?

TO DO

# what are the key artifacts?

bin\alby.assemblyAttributes.exe
bin\alby.assemblyAttributes.exe.config
bin\the atl dll TO DO


# what's an example of running the test program?

C:\albyStuff\development\alby.assemblyShellExtension>

bin\alby.testAssemblyAttributes.exe alby.assemblyAttributes.exe "..\alby.adventureworks2008\bin\alby.adventureworks2008.codegen.dll"


# what was this developed and tested on?

visual studio 2013

window 8

# alby's c++ wide character best bet:

- use windows xxxW functions wherever possible 
- use std::wstring internally
- use std::string  externally, ie cout, file io
- repeat: never ever send utf16 wstring's to io, only ever send utf8 string's

