#pragma once
#include "SPingPre.h"
#include<initializer_list>
#include<utility>
#include<math.h>
#include"Common.h"
#include <iostream>
#include <ostream>
#include <cassert>

namespace spmath
{
    
// T 不能是引用类型 增加检查下？
template <typename T, size_t Size>
class SP_API Vector{
public:
    using this_type             = Vector<T, Size>;
    using traits                = VectorTraits<this_type>;
    using value_type            = T;
    using lvalue_reference      = std::add_lvalue_reference_t<value_type>;
    using const_reference       = std::add_lvalue_reference_t<std::add_const_t<value_type>>;
    using pointer               = std::add_pointer_t<value_type>;
    using const_pointer         = std::add_pointer_t<T const>;
    using index_sequence_type   = std::make_index_sequence<Size>;
    
    
    constexpr static size_t size = Size;

    // 构造函数体 为空的时候 可以声明为 constexpr(或者构造体里面也是常量的)，可以构造一个字面值常量类
    constexpr Vector(): Vector(T{0}, index_sequence_type{}) {};
    constexpr Vector(const std::initializer_list<T> & list): Vector(list.begin(), index_sequence_type{}) {};
    constexpr Vector(const_pointer p): Vector(p, index_sequence_type{}) {};
    Vector(const Vector& vec): Vector(vec.data_.begin()) {};


    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type& assign(const Vector<U, Size>& v) {
        for(size_t i=0; i < size; i++) data_[i] = v.data_[i];
        return *this;
    }

    bool operator == (const Vector& v) {return this->data_ == v.data_;}
    bool operator != (const Vector& v) {return !(*this == v); }

    value_type& operator [] (size_t index) {
        // assert((index < size) && "Vector [] Index out of range");
        return data_[index];
    }

    const value_type& operator [] (size_t index) const {
        // assert((index < size)  && "Vector [] Index out of range");
        return data_[index];
    }

    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type operator + (const Vector<U, Size>& v)
    {
        Vector nv(*this);
        return nv += v;
    }

    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type& operator += (const Vector<U, Size>& v)
    {
        for(size_t i=0; i < size; i++) data_[i] += v.data_[i];
        return *this;
    }

    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type operator - (const Vector<U, Size>& v) {
        Vector nv(*this);
        return nv -= v;
    }

    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type& operator -= (const Vector<U, Size>& v) {
        for(size_t i=0; i < size; i++) data_[i] -= v.data_[i];
        return *this;
    }


    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type operator * (const Vector<U, Size>& v) {
        Vector nv(*this);
        return nv *= v;
    }

    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type& operator *= (const Vector<U, Size>& v) {
        for(size_t i=0; i < size; i++) data_[i] *= v.data_[i];
        return *this;
    }

    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type operator / (const Vector<U, Size>& v) {
        Vector nv(*this);
        return nv /= v;
    }

    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type& operator /= (const Vector<U, Size>& v) {
        for(size_t i=0; i < size; i++) data_[i] /= v.data_[i];
        return *this;
    }

    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type& operator *= (U v) {
        for(size_t i=0; i < size; i++) data_[i] *= v;
        return *this;
    }

    template<typename U, typename=enable_if_convert_t<T, U>>
    this_type operator * (U v) {
        Vector nv(*this);
        return nv *= v;
    }


    this_type& Normalize(){
        static_assert(!std::is_same_v<value_type, int>, "Vector<int> can not nomalize");
        float length = Length();
        return (*this) *= 1 / length;
    }
    float Length() {
        return std::sqrt(LengthSquared());
    }

    float LengthSquared() {
        float sum = 0;
        for(size_t i=0; i < size; i++) sum += data_[i] * data_[i];
        return sum;
    }


    template<size_t N>
    lvalue_reference at()
    {
        static_assert(N < size, "Error vector at out of range");
        return data_[N];
    }

    template<size_t N>
    constexpr const_reference at() const
    {
        static_assert(N < size, "Error vector at out of range");
        return data_[N];
    }
    

    static const this_type& Zero()
    {
        static const this_type zero;
        return zero;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) 
    {
        os << std::endl << " Vector: ";
        for(size_t i=0; i < size; i++) os << v.data_[i] << ",";
        os << std::endl;
        return os;
    }


// ----------Vector3 特有的方法---------------
    template<typename U, typename S, size_t size, typename =std::enable_if_t<size==3>>
    Vector& Cross(const Vector<U, size>& v1, const Vector<S, size>& v2)
    {
        x = v1.y * v2.z - v1.z * v2.y;
		y = v1.z * v2.x - v1.x * v2.z;
		z = v1.x * v2.y - v1.y * v2.x;
        return *this;
    }

    template<typename U, size_t size, typename =std::enable_if_t<size==3>>
    Vector Cross(const Vector<U, size>& v2)
    {
        Vector v(*this);
        v.Cross(*this, v2);
        return v;
    }

// ----------Vector3 特有的方法---------------

public:
    using data_type = std::array<T, Size>;
    union 
    {
        data_type data_;
        struct {T x, y, z;};
    };

private:

    template<size_t ...Index>
    constexpr Vector(value_type t, std::index_sequence<Index...>) : data_({(Index, t)...}){}
    template<size_t ...Index>
    constexpr Vector(const_pointer p, std::index_sequence<Index...>): data_({(Index, *p++)...}) {}
    

private:
     
};

using Vec3 = Vector<float, 3>;
using Vec3i = Vector<int, 3>;
using Vec3d = Vector<double, 3>;

using Vec4 = Vector<float, 4>;
using Vec4i = Vector<int, 4>;
using Vec4d = Vector<double, 4>;

using Vec2 = Vector<float, 2>;
using Vec2i = Vector<int, 2>;
using Vec2d = Vector<double, 2>;

} // namespace spmath
