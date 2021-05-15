#include "spdlog/spdlog.h"
#include <iostream>

int main()
{
	spdlog::info("Welcome to spdlog!");
	spdlog::error("Some error message with arg: {}", 1);

	spdlog::warn("Easy padding in numbers like {:08d}", 12);
	spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	spdlog::info("Support for floats {:03.2f}", 1.23456);
	spdlog::info("Positional args are {1} {0}..", "too", "supported");
	spdlog::info("{:<30}", "left aligned");

	spdlog::set_level(spdlog::level::debug); // Set global log level to debug
	spdlog::debug("This message should be displayed..");

	// change log pattern
	spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

	// Compile time log levels
	// define SPDLOG_ACTIVE_LEVEL to desired level
	SPDLOG_TRACE("Some trace message with param {}", 42);
	SPDLOG_DEBUG("Some debug message");

	int* a = (int*)malloc(4);
	*a = 5;
	std::cout << a << std::endl << *a;
	

	void* b = VirtualAlloc(NULL, 1000, MEM_COMMIT, PAGE_READWRITE);
	void* c = VirtualAlloc(NULL, 1000, MEM_COMMIT, PAGE_READWRITE);
	std::cout << b << std::endl << c;

	for (int i = 1; i < 5; i++) 
	{

	}



}