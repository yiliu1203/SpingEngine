#pragma once

#include "Object.h"
#include "SPingPre.h"

namespace SPing {
// todo 怎么加上约束， 继承 Object的才行？
template <typename T, typename = decltype(T::GetTypeInfoStatic())>
class SharePtr
{
public:
    SharePtr(const SharePtr<T>& rhs) noexcept
        : ptr_(rhs.ptr_)
    {
        assert(ptr_ != nullptr);
        AddRef();
    }

    SharePtr(SharePtr<T>&& rhs) noexcept
        : ptr_(rhs.ptr_)
    {
        assert(ptr_ != nullptr);
        rhs.ptr_ = nullptr;
    }

    explicit SharePtr(T* ptr) noexcept
        : ptr_(ptr)
    {
        ptr_->AddRef();
    }

    ~SharePtr() { ReleaseRef(); }

    /**
     * 这里有个 copy -swap的技巧模式
    */
    SharePtr<T>& operator=(const SharePtr<T>& rhs)
    {
        if (ptr_ == rhs.ptr_) return;
        SharePtr<T> tmpCopy(rhs);
        // using std::swap;
        Swap(rhs);
    }

    SharePtr<T>& operator=(T* ptr)
    {
        if (ptr_ == ptr) return;
        SharePtr<T> tmpCopy(ptr);
        Swap(rhs);
    }

    T* operator->() const
    {
        assert(ptr_ != nullptr);
        return ptr_;
    }

    T& operator*() const
    {
        assert(ptr_ != nullptr);
        return *ptr_;
    }

    bool    operator==(const SharePtr<T>& rhs) const { return ptr_ == rhs.ptr__; }
    boolean operator!=(const SharePtr<T>& rhs) const { return !(*this == rhs); }


    void Swap(SharePtr<T>& rhs) { SPing::Swap(ptr_, rhs.ptr_); }

    T* Get() const { return ptr_; }

    int Refs() const { return ptr_->Refs(); }

    int WeakRefs() const { return ptr_->WeakRefs(); }


private:
    void AddRef() noexcept { ptr_->AddRef(); }

    void ReleaseRef() noexcept
    {
        if (ptr_) {
            ptr_->ReleaseRef();
            ptr_ = nullptr;
        }
    }
    T* ptr_;
};
}   // namespace SPing