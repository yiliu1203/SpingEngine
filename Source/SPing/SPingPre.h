#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <sstream>

#include <algorithm>
#include <map>
#include <functional>
#include <type_traits>
#include <wchar.h>
#include <assert.h>
#include "MacroConfig.h"

#ifdef SP_PLATFORM_WIN
	#include <Windows.h>
#endif




#ifndef SP_CORE_H

	#define SP_CORE_H

	#ifdef SP_PLATFORM_WIN

		#ifdef SP_BUILD_DLL
			#define SP_API __declspec(dllexport)
		#else
			#define SP_API
		#endif
	#endif	

	

	// ---------------BIT--------------------
	#define BIT(x) 1 << x


#endif
