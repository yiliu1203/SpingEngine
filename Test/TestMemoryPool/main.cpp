
#include <iostream>
#include "MemManager.h"
#include <string>
#include <vector>

class Test : public SP::MemObj
{
public:
	Test(int _a, int _b, int _c) : a(_a), b(_b) {

	}
	int a;
	int b;
	int c;
};

int main()
{
	auto t1 = new Test(1, 3, 5);
	std::cout << t1->a << std::endl;

	auto t2 = new Test(1, 3, 5);
	std::cout << t2->a << std::endl;
	delete t2;
	delete t1;

	std::vector<Test *> tV;
	for (int i = 0; i < 50000; i++) {
		tV.push_back(new Test(1, 3, 5));
	}

	for (int i = 0; i < tV.size(); i++) {
		delete tV[i];
		std::cout << "del" << i;
	}


	

}