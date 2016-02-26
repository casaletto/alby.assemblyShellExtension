
https://msdn.microsoft.com/en-us/library/windows/desktop/ms682499(v=vs.85).aspx
https://msdn.microsoft.com/en-us/library/windows/desktop/cc144067(v=vs.85).aspx
https://msdn.microsoft.com/en-us/library/windows/desktop/cc144106(v=vs.85).aspx
https://msdn.microsoft.com/en-us/library/windows/desktop/hh127448(v=vs.85).aspx

http://www.codeproject.com/Articles/441/The-Complete-Idiot-s-Guide-to-Writing-Shell-Extens
http://www.codeproject.com/Articles/463/The-Complete-Idiots-Guide-to-Writing-Shell-Exten


[AttributeUsage(AttributeTargets.Assembly)]
public class MyCustomAttribute : Attribute {
    string someText;
    public MyCustomAttribute() : this(string.Empty) {}
    public MyCustomAttribute(string txt) { someText = txt; }
    ...
}


var attributes = assembly
    .GetCustomAttributes(typeof(MyCustomAttribute), false)
    .Cast<MyCustomAttribute>();
	

GitAttributes

GitCommit
GitBranch
GitUrl
StashUrl

