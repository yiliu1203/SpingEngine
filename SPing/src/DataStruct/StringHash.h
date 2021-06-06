#include "SPingPre.h"
namespace SPing {

	class SP_API StringHash {
	public:
		StringHash() noexcept : value_(0)
		{};
		StringHash(const StringHash& rhs) noexcept = default;
		StringHash(const StringHash&& rhs) noexcept
		{
			value_ = rhs.value_;
			std::cout << "const StrHash&& rhs" << std::endl;
		}
		explicit StringHash(std::size_t val) noexcept : value_(val) {}
		explicit StringHash(std::string& str) {
			value_ = std::hash<std::string>{}(str);
		}
		explicit StringHash(std::string str) {
			value_ = std::hash<std::string>{}(str);
		}
		bool operator == (const StringHash& rhs) const {
			return value_ == rhs.value_;
		}
		bool operator != (const StringHash& rhs) const {
			return (value_ != rhs.value_);
		}

	private:
		std::size_t value_;
	};
}