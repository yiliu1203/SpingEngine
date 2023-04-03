#pragma once

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