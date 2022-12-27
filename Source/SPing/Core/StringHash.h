#pragma once
#include "SPingPre.h"

// 将字符串 hash 成 unsigned 类型，方便比较,提高效率。
// hash 冲突怎么解决 todo

namespace SPing {

	class SP_API StringHash {
	public:
		StringHash() noexcept : value_(0)
		{
        };
		StringHash(const StringHash& rhs) noexcept{
			value_ = rhs.value_;
			std::cout << "const StrHash& rhs" << std::endl;
		};

		StringHash(StringHash&& rhs) noexcept
		{
			value_ = rhs.value_;
			std::cout << "const StrHash&& rhs" << std::endl;
		}
		
        explicit StringHash(std::size_t val) noexcept : value_(val) 
        {
        }
        
		explicit StringHash(const std::string& str)
        {
			value_ = std::hash<std::string>{}(str);
		}

        explicit StringHash(const char* val) 
        {
            value_ = std::hash<std::string>{}(val);
        }

		bool operator == (const StringHash& rhs) const 
        {
			return value_ == rhs.value_;
		}

		bool operator != (const StringHash& rhs) const 
        {
			return (value_ != rhs.value_);
		}
        
		bool operator < (const StringHash& rhs) const
		{
			return (value_ < rhs.value_);
		}

		friend std::ostream& operator << (std::ostream& out, const StringHash& val);

	private:
		std::size_t value_;
	};
}