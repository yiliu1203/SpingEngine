#pragma once
#include <exception>
#include <string>
#include <string_view>
#include <vector>

class ExceptionMsg
{
public:
    template <typename... A>
    ExceptionMsg(const char* _file_, const char* _line_, A... a): msgs_{0} {
        msgs_.push_back(std::string(a))...;
        msgs_.push_back(std::string(_file_));
        msgs_.push_back(std::string(_line_)); 
    }

    const char* cStr() {
        std::string msg;
        for(auto& item : msgs_) {
            msg += item;
        }
        return msg.c_str();
    };

    std::vector<std::string> msgs_;

};

#define RTTI_ERROR(...) throw std::exception( (std::string(__VA_ARGS__) + std::string(" file: ") +  std::string( __FILE__) + std::to_string(__LINE__)).c_str());


#ifndef SP_API
    #define SP_API
#endif
