using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection ;
using System.IO ;
using sd = System.Diagnostics ;

namespace alby.assemblyAttributes   
{
	public class Program
	{
		public static int Main( string[] args )
		{
			Console.OutputEncoding = Encoding.UTF8 ;

			sd.Trace.WriteLine( "alby.assemblyAttributes [start]" ) ;

			try
			{
				AppDomain.CurrentDomain.AssemblyResolve += AssemblyResolve;

				var dic = new Dictionary<string, string> { };

				var ass = Assembly.GetExecutingAssembly();

				if ( args.Length >= 1 )
				{
					var filename = args[0] ;
					var fullpath = Path.GetFullPath( filename ) ;
					dic.Add( "AssemblyPath", fullpath ) ;

					try
					{
						ass = Assembly.LoadFrom( new Uri( fullpath ).AbsoluteUri ) ;
					}
					catch( FileNotFoundException ex )
					{
						sd.Trace.WriteLine( ex.ToString() ) ;

						ass = Assembly.LoadFile( fullpath ) ;
					}
				}

				dic.Add( "AssemblyVersion", ass.GetName().Version.ToString() ) ;
				dic.Add( "AssemblyFullName", ass.FullName );
				dic.Add( "AssemblyProcessorArchitecture", ass.GetName().ProcessorArchitecture.ToString() ) ;

				ass.GetCustomAttributesData().ToList().ForEach(i =>
				{
					object value = "" ;
					i.ConstructorArguments.Take(1).ToList().ForEach( k => value = k.Value ) ;

					value = value ?? "" ;

					var key = i.AttributeType.Name.Replace( "Attribute", "" ) ;

					if ( ! dic.ContainsKey( key ) )
						   dic.Add( key, value.ToString() ) ;
				});

				// dump
				var keys = dic.Keys.ToList() ;
				keys.Sort() ;
				keys.ForEach( k => 
				{
					var v = dic[k] ;
					Console.WriteLine( "{0}|{1}", k, v ) ;
				}) ;

				return 0;
			}
			catch( Exception ex )
			{
				sd.Trace.WriteLine( ex.ToString() ) ;

				Console.Error.WriteLine("EXCEPTION");
				Console.Error.WriteLine( ex.ToString() ) ;
				return 1 ;
			}
			finally
			{
				Console.Out.Flush();
				Console.Error.Flush();

				sd.Trace.WriteLine("alby.assemblyAttributes [finish]");				
			}

		} // end main

		public static Assembly AssemblyResolve(object src, ResolveEventArgs a )
		{ 
			return null ;
		}

	} // end class
}

