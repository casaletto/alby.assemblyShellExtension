#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"

#include <stdio.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>

#include <windows.h>
#include <shlobj.h>
#include <comdef.h>
#include <atlbase.h>
#include <atlconv.h>
#include <atlcom.h>
#include <atlctl.h>

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <clocale>
#include <locale>
#include <codecvt>
#include <fstream>
#include <map>
#include <iomanip>
#include <ctime>
#include <algorithm>


