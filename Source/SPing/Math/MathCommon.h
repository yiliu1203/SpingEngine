#pragma once
#include<type_traits>
#include <vector>

#define INLINE __forceinline
namespace SPing::Math
{
    // 主模板
    template<typename T, typename U, typename S=std::void_t<>>
    struct enable_if_convert : std::false_type{};

    // 偏特化
    template<typename T, typename U>
    struct enable_if_convert<T, U, std::enable_if_t<std::is_same_v<T, std::common_type_t<T, U>>>> : std::true_type{};
    
    template<typename T, typename U>
    using enable_if_convert_t = typename enable_if_convert<T, U>::type;


    template<typename T, size_t Size>
    class Vector;

    template<typename T, size_t Size>
    class Matrix;

    // 主模板，接受一个类型参数
    template<typename T>
    class VectorTraits;
    // 偏特化, 这个 Vector 会被推导为 Vector 类型，从而上面声明的Vector类型确定了
    template<typename T, size_t Size>
    class VectorTraits<Vector<T, Size>>{

    };


    template<typename T>
    class MatrixTraits;

    template<typename T, size_t Size>
    class MatrixTraits<Matrix<T, Size>>{
    public:
        using row_type = Vector<T, Size>;

    };





} // namespace spmath
