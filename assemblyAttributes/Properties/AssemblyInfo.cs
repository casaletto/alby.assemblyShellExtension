using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using assemblyAttributes ;

[assembly: AssemblyTitle("alby.assemblyAttributes")]
[assembly: AssemblyDescription("alby.assemblyAttributes")]
[assembly: AssemblyConfiguration("alby.assemblyAttributes")]
[assembly: AssemblyCompany("casaletto PL")]
[assembly: AssemblyProduct("alby.assemblyAttributes")]
[assembly: AssemblyCopyright("copyright ©  2016 Casaletto PL")]
[assembly: AssemblyTrademark("Casaletto PL")]
[assembly: AssemblyCulture("")]
[assembly: ComVisible(false)]
[assembly: Guid("4fef644f-53b6-4bfe-93bf-9328ce6e2147")]

[assembly: AssemblyVersion("1.0.0.1")]
[assembly: AssemblyFileVersion("1.0.0.2")]
[assembly: AssemblyInformationalVersion( "1.0.0.3") ]

[assembly: MyCustomAssemblyAttribute("Custom attribute text")]

[assembly: GitCommitAttribute("7e9d047cddcc93d2f72639a0b959ba2649b75183")] 
[assembly: GitBranchAttribute("master")]
[assembly: GitUrlAttribute("ssh://git@github.com:casaletto/alby.assemblyShellExtension.git")]
[assembly: BitBucketUrlAttribute("https://bitbucket.org/eigen/eigen/branches")]
