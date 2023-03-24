#pragma once
#include <exception>
#include <initializer_list>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>


class CommonException : public std::exception
{
public:
    CommonException(const std::string& _file_, size_t _line_, const std::string& _func_,
                    std::initializer_list<std::string> initial_list)
    {
        std::stringstream ss;
        // (ss << a << " ")...;
        for (auto item : initial_list) {
            ss << item << " ";
        }
        ss << "file:" << _file_;
        ss << "line:" << _line_;
        ss << "func:" << _func_;
        msg_ = ss.str();
    }

    const char* what() { return msg_.c_str(); };

private:
    std::string msg_;
};

#define RTTI_ERROR(...)                                                                           \
    {                                                                                             \
        CommonException exception = CommonException(__FILE__, __LINE__, __func__, {__VA_ARGS__}); \
        std::cout << exception.what();                                                            \
        throw exception;                                                                          \
    }

#define ASSERT(condition, ...)      \
    {                               \
        if (!(condition)) {         \
            RTTI_ERROR(__VA_ARGS__) \
        }                           \
    }

// #define RTTI_ERROR(...)
#ifndef SP_API
#    define SP_API
#endif
