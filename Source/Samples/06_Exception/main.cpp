#include <exception>
#include <vector>
#include <memory>
#include <iostream>
#include <assert.h>
#include <initializer_list>
#include <string>
#include <sstream>


class Error : public std::exception
{
public:
    virtual const char* what() const {
        return msg.c_str();
    }

    Error(const std::string& _file_, const size_t _line_, const std::string& _func_, std::initializer_list<std::string> msg_list) {
        std::stringstream ss;
        for (auto& item : msg_list)
            ss << item << " ";
        ss << "[file: " << _file_;
        ss << ", lineno: " << _line_;
        ss << ", func: " << _func_ << "]" << std::endl;
        msg = ss.str();
    }
private:
    std::string msg;
};

#define ERROR(...) { Error error = Error(__FILE__, __LINE__, __func__, {__VA_ARGS__}); std::cout << error.what() << std::endl; throw error;};


void test1() {
    ERROR("tttttttttttttttttttttttt","asdf");
}

int main() {
    using namespace std;
    {
        cout << "----------------Test Debug Macro--------------" << endl;
        test1();
    }
    return 0;
}