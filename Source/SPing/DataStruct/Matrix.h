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

template<typename T, size_t Size>
class SP_API  Matrix{
public:
    using this_type                 = Matrix<T, Size>;
    using traits                    = MatrixTraits<this_type>;
    using value_type                = T;
    using lvalue_reference          = std::add_lvalue_reference_t<value_type>;
    using const_reference           = std::add_lvalue_reference_t<std::add_const_t<value_type>>;
    using pointer                   = std::add_pointer_t<value_type>;
    using const_pointer             = std::add_pointer_t<T const>;
    using row_type                  = typename traits::row_type;
    using row_index_sequence_type   = std::make_index_sequence<Size>;
    using row_iterator              = row_type *;
    using const_row_iterator        = const row_type *;
    using all_index_sequence_type   = std::make_index_sequence<Size*Size>;
    
    constexpr static size_t size = Size;
    constexpr static size_t rols = Size;
    constexpr static size_t cols = Size;

    constexpr Matrix(const std::initializer_list<const std::initializer_list<value_type>>& list) : Matrix(list, row_index_sequence_type{}){};

public:
    using data_type = std::array<row_type, Size>;
    data_type data_;


private:
    
    template<size_t ...N>
    constexpr Matrix(const std::initializer_list<const std::initializer_list<value_type>>& list, std::index_sequence<N...>)
    :data_({row_type(*(list.begin() + N))...})
    {}
};


using Matrix3f = Matrix<float, 3>;

} // namespace spmath
