#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <memory>
#include <Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <functional>
#include <filesystem>
#include <time.h>
#include <string>


#include "RBT.h"


#pragma comment(lib,"msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")


template<typename ... Args>
std::wstring format_string(const std::wstring& format, Args ... args)
{
    size_t size = swprintf(nullptr, 0, format.c_str(), args ...) + 1;
    std::unique_ptr<wchar_t[]> buffer(new wchar_t[size]);
    swprintf(buffer.get(), size, format.c_str(), args ...);
    return std::wstring(buffer.get(), buffer.get() + size - 1);
}

