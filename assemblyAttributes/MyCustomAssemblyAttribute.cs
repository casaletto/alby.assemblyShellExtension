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
		string _txt;

		public MyCustomAssemblyAttribute() : this( string.Empty ) 
		{
		}

		public MyCustomAssemblyAttribute(string txt) 
		{ 
			_txt = txt; 
		}
	}

	[AttributeUsage(AttributeTargets.Assembly)]
	public class GitCommitAttribute : Attribute
	{
		string _txt;

		public GitCommitAttribute()
			: this(string.Empty)
		{
		}

		public GitCommitAttribute(string txt)
		{
			_txt = txt;
		}
	}

	[AttributeUsage(AttributeTargets.Assembly)]
	public class GitBranchAttribute : Attribute
	{
		string _txt;

		public GitBranchAttribute()
			: this(string.Empty)
		{
		}

		public GitBranchAttribute(string txt)
		{
			_txt = txt;
		}
	}

	[AttributeUsage(AttributeTargets.Assembly)]
	public class GitUrlAttribute : Attribute
	{
		string _txt;

		public GitUrlAttribute()
			: this(string.Empty)
		{
		}

		public GitUrlAttribute(string txt)
		{
			_txt = txt;
		}
	}

	[AttributeUsage(AttributeTargets.Assembly)]
	public class BitBucketUrlAttribute : Attribute
	{
		string _txt;

		public BitBucketUrlAttribute()
			: this(string.Empty)
		{
		}

		public BitBucketUrlAttribute(string txt)
		{
			_txt = txt;
		}
	}

}
