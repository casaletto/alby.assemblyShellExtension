using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace assemblyAttributes
{
	[AttributeUsage(AttributeTargets.Assembly)]
	public class MyCustomAssemblyAttribute : Attribute 
	{
		string someText;

		public MyCustomAssemblyAttribute() : this( string.Empty ) 
		{
		}

		public MyCustomAssemblyAttribute(string txt) 
		{ 
			someText = txt; 
		}
	}
}
