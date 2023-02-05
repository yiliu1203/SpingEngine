#pragma once
#include <exception>
#include <string>

#define RTTI_ERROR(...) throw std::exception( (std::string(__VA_ARGS__) + std::string(" file: ") +  std::string( __FILE__) + std::to_string(__LINE__)).c_str());
    

