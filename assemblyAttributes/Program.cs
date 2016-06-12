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
		public static string __filename = "" ;
		public static string __fullpath = "" ;

		public static int Main( string[] args )
		{
			Console.OutputEncoding = Encoding.UTF8 ;

			sd.Trace.WriteLine( "alby.assemblyAttributes [start]" ) ;

			try
			{
				if ( args.Length == 0 )
					 throw new Exception( "usage: alby.assemblyAttributes [assemblyFullPath]" )  ;

				AppDomain.CurrentDomain.AssemblyResolve += AssemblyResolve ;

				__filename = args[0] ;
				__fullpath = Path.GetFullPath( __filename ) ;

				var ass = Assembly.LoadFile( __fullpath ) ;

				var dic = new Dictionary<string, string> {} ;

				dic.Add( "AssemblyPath",					__fullpath ) ;
				dic.Add( "AssemblyVersion",					ass.GetName().Version.ToString() ) ;
				dic.Add( "AssemblyFullName",				ass.FullName ) ;
				dic.Add( "AssemblyProcessorArchitecture",	ass.GetName().ProcessorArchitecture.ToString() ) ;

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

				sd.Trace.WriteLine( "alby.assemblyAttributes [finish]" ) ;				
			}

		} // end main

		public static Assembly AssemblyResolve( object src, ResolveEventArgs rea )
		{
			sd.Trace.WriteLine( "[resolve] " + rea.Name ) ;

			if ( string.IsNullOrWhiteSpace( __fullpath ) ) return null ;

			var folder = Path.GetDirectoryName( __fullpath ) ;

			var files = Directory.GetFiles( folder, "*.*", SearchOption.AllDirectories )
								 .Where( f => f.ToUpper().EndsWith( ".DLL" ) || 
											  f.ToUpper().EndsWith( ".EXE" ) ) ;
			foreach( var file in files )
			{
				try
				{
					var assemblyName = AssemblyName.GetAssemblyName( file ) ;
					if ( rea.Name == assemblyName.ToString() )
					{
						sd.Trace.WriteLine( "[resolved] " + file ) ;
						return Assembly.LoadFile( file ) ;
					}
				}
				catch( Exception ex )
				{
					sd.Trace.WriteLine( ex.ToString() ) ;				
				}
			}

			return null ;
		}

	} // end class
}

