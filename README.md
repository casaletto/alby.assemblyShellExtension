# alby.assemblyShellExtension

a tool to let you see your .net assembly attributes in windows explorer's properties dialog


how to build:

visual studio 2013:
msbuild alby.assemblyShellExtension.sln /t:Clean,Rebuild /p:Configuration=Release /p:Platform=x64

key artifacts:
bin\alby.assemblyAttributes.exe
bin\alby.assemblyAttributes.exe.config
bin\the atl dll


