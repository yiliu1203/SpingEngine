# 记录一些总结
```c++
    template <typename T>
    // 【如果匹配到 const int *, 则这里的 T == const int *&】
    Value(T&& val)
    {
        ref_type_ = trait::RefTrait<T>::value;
        is_const_ = trait::IsConst<T>::value;
    }
```