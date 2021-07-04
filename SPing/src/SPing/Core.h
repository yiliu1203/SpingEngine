

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

	//----------------------------------------

	
	// ---------------------SP_ASSERT----------------
	
	#ifdef SP_ENABLE_ASSERT
	
		#define SP_ASSERT(x, ...) {if(!x){SP_ERR("Assert Failed:{0}", __VA_ARGS__); __debugbreak();}}
		#define SP_CORE_ASSERT(x, ...) {if(!x){SP_CORE_ERR("Assert Failed:{0}", __VA_ARGS__); __debugbreak();}}

	#else

		#define SP_ASSERT(x, ...)
		#define SP_CORE_ASSERT(x, ...)

	#endif // SP_ENABLE_ASSERT
	
	//---------------------------------------------------


#endif

