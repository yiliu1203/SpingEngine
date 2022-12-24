#include <Windows.h>
#include "Test.h"
// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
// {
// 	return 1;
// }

int main() {

	MyClass t;
	auto r = t.Add(1, 2);
	std:: cout << r << std::endl;

	return 0;
}