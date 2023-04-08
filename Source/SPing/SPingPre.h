#pragma once



#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#include "Core/Utils.h"
#include "MacroConfig.h"
#include <algorithm>
#include <assert.h>
#include <functional>
#include <map>
#include <type_traits>
#include <wchar.h>


#ifdef SP_PLATFORM_WIN
#    include <Windows.h>
#endif

#ifndef SP_CORE_H

#    define SP_CORE_H

#    ifdef SP_PLATFORM_WIN

#        ifdef SP_BUILD_DLL
#            define SP_API __declspec(dllexport)
#        else
#            define SP_API
#        endif
#    endif
// ---------------BIT--------------------
#    define BIT(x) 1 << x
#endif