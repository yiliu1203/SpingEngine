#include <exception>
#include <vector>
#include <memory>
#include <iostream>
#include <assert.h>
#include <initializer_list>
#include <string>
#include <sstream>
#include <tuple>

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

template <typename... A>
void OUT(A... args) {
    auto a = std::forward_as_tuple(args...);
    OUT(a, std::make_index_sequence<sizeof... (A)>{});
}

template<typename... A, size_t ...N>
void OUT(std::tuple<A...>& a, std::index_sequence<N...>)
{
    // 这里本质是利用模板实例化的过程，也需要用这个特征才能在生成 实例化 std::get
    std::initializer_list<int> tmp = { (std::cout << std::get<N>(a) << " ",0)... };
}




#define ERROR(...) { Error error = Error(__FILE__, __LINE__, __func__, {__VA_ARGS__}); std::cout << error.what() << std::endl; throw error;};

#define ERROR2(...) OUT(__VA_ARGS__);

void test1() {
    ERROR("tttttttttttttttttttttttt","asdf");
    ERROR2("ADSFAD");
}

int main() {
    using namespace std;
    {
        cout << "----------------Test Debug Macro--------------" << endl;
        test1();
        // ERROR2("ADSFAD");
        // std::tuple<int, int> testTuple{1, 2};
        // std::get<0>(testTuple);     // std::get<x> 需要编译期常量
        // OUT("asdfa", 1, "asdf");

    }
    return 0;
}