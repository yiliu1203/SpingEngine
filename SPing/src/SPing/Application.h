#ifndef SP_APPLICATION_H

#define SP_APPLICATION_H

#include "Core.h"
#include <stdio.h>

#define SP_API __declspec(dllexport)  // ∆Ê›‚¡À°£°£°£

namespace SPing {

	class SP_API Application
	{
	public:
		Application();
		virtual  ~Application(); 
		void Run();

	};

#ifdef SP_API
	void __declspec(dllexport) Print()
	{
		printf("Hello");
	}


#endif // DEBUG
	
	

}



#endif
