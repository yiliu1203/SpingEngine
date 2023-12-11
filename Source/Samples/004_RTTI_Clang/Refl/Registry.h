#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

/**
 * 将TypeDescriptor 注册到 Registry, 这样TypeDescriptor 全局唯一
 * 
 * 在Clear函数中使用了swap来清空容器，这样的好处是可以使容器完全重置，如果直接使用clear的话会保留原来的容器大小。
*/

namespace Refl
{

class TypeDescriptor;

class Registry
{

public:
    static Registry& Instance() {
        static Registry s_instance;
        return s_instance;
    }

    Registry& Register(std::unique_ptr<TypeDescriptor> type_desc);
    void Clear()
    {
        /**
         * 在Clear函数中使用了swap来清空容器，这样的好处是可以使容器完全重置，如果直接使用clear的话会保留原来的容器大小。
        */
        decltype(_descs) tmp;
        _descs.swap(tmp);
    }

private:

    std::unordered_map<std::string, std::unique_ptr<TypeDescriptor>> _descs;


};

}