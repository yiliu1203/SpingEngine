#ifndef SP_ENTRY_H
#define SP_ENTRY_H

#ifdef SP_PLATFORM_WIN

extern SPing::Application* SPing::CreateApplication();

int main(int argc, char** argv)
{
	SPing::Log::Init();
	auto app = SPing::CreateApplication();
	
	SP_INFO("App Initial");

	app->Run();
	return 1; 
}



#endif // SP_PLATFROM_WIN
 


#endif

