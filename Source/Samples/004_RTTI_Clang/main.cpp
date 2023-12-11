#include "Refl/Refl.h"

#include <iostream>

class Foo {
public:
	void Func(std::string a) { std::cout << " exec Func : " << a << std::endl; }
};

int main() {
	Refl::MemberFunction func(&Foo::Func);

	std::string str = "Hello, world!";

	Foo foo;
	int a = 1;
	func.Invoke(foo, str);

	return 0;
}