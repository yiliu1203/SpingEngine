#pragma once
#include "../Reflect/Meta.h"
#include "../Reflect/TypeIndex.h"
#include "SPingPre.h"
#include "StringHash.h"
#include "TypeAlias.h"
#include <type_traits>




namespace SPing {

class Context;
using TypeInfo = reflect::Meta;
// class TypeInfo;
// class TypeId;

// class SP_API TypeInfo
// {
// public:
//     TypeInfo(const std::string& typeName, const TypeInfo* baseTypeInfo)
//         : typeName_(typeName)
//         , baseTypeInfo_(baseTypeInfo)
//         , type_(typeName)
//     {}
//     ~TypeInfo() = default;
//     const std::string& GetTypeName() const { return typeName_; }
//     const StringHash&  GetType() const { return type_; }
//     const TypeInfo*    getBaseTypeInfo() const { return baseTypeInfo_; }

//     bool IsTypeOf(const StringHash& type) const
//     {
//         if (type_ == type) return true;
//         const TypeInfo* base = getBaseTypeInfo();
//         while (base != nullptr) {
//             if (base->GetType() == type) return true;
//             base = base->getBaseTypeInfo();
//         }
//         return false;
//     };

//     bool IsTypeOf(const std::string& typeName) const
//     {
//         if (typeName_ == typeName) return true;
//         const TypeInfo* base = getBaseTypeInfo();
//         while (base != nullptr) {
//             if (base->GetTypeName() == typeName) return true;
//             base = base->getBaseTypeInfo();
//         }
//         return false;
//     }

// private:
//     std::string      typeName_;
//     const StringHash type_;
//     const TypeInfo*  baseTypeInfo_;
// };



/**
	 * 这个结构没有合并到 RefCounted 中最大的原因还是为了 WeakPtr的实现，
	 * WeakPtr 会有成员指向 RefCount。Object extend RefCounted, object析构时父类自然也析构了，但是RefCount_不一定跟着析构
	 * WeakPtr 中也指向了RefCount，增加了弱引用的计数。 弱引用计数为0时才会真正析构 RefCount_
	*/
struct SP_API RefCount
{
    int refs_;
    int weakRefs_;
    RefCount()
        : refs_(0)
        , weakRefs_(0){};
    ~RefCount()
    {
        refs_     = -1;
        weakRefs_ = -1;
    }
};

class SP_API RefCounted
{
public:
    RefCounted()
        : refCount_(new RefCount())
    {
        refCount_->weakRefs_ = 1;
    };

    virtual ~RefCounted()
    {
        std::cout << "~RefCounted" << std::endl;
        assert(refCount_->refs_ == 0);
        assert(refCount_->weakRefs_ >= 1);

        refCount_->refs_ = -1;   // 让其他非法访问的时候触发 asset
        // 这里很关键，这个对象如果还有弱引用，则还是可以访问弱引用计数器的
        // 这个对象本身不能再访问计数器
        if (--refCount_->weakRefs_ == 0) {
            delete refCount_;
        }
        refCount_ = nullptr;
    };

    RefCounted(RefCounted& r)            = delete;
    RefCounted& operator=(RefCounted& r) = delete;
    void        AddRef()
    {
        // new 出来 初始值是 0；
        assert(refCount_->refs_ >= 0);

        refCount_->refs_++;
    };
    void ReleaseRef()
    {
        assert(refCount_->refs_ > 0);
        assert(refCount_->weakRefs_ >= 1);
        refCount_->refs_--;
        if (refCount_->refs_ == 0) delete this;
    };
    int Refs() const { return refCount_->refs_; };
    int WeakRefs() const { return refCount_->weakRefs_ - 1; };

private:
    RefCount* refCount_;
};


class SP_API Object : public RefCounted
{
public:
    Object(Context* context) { context_ = context; }
    virtual ~Object(){};

    static const TypeInfo*    GetTypeInfoStatic() { return nullptr; }
    virtual const TypeId&     GetType() const     = 0;
    virtual const std::string GetTypeName() const = 0;
    virtual const TypeInfo*   GetTypeInfo() const = 0;
    bool                      IsInstanceOf(const TypeId& type) const { return this->GetTypeInfo()->IsTypeOf(type); }
    bool IsInstanceOf(const TypeInfo* typeInfo) const { return this->GetTypeInfo()->IsTypeOf(typeInfo->id()); }

    template <typename T>
    bool IsInstanceOf() const
    {
        return IsInstanceOf(T::GetTypeInfoStatic());
    }

private:
    Context* context_;
};

// static const TypeInfo staticInfo(#TYPE_NAME, BASE_TYPE_NAME::GetTypeInfoStatic());

#define TYPE_RTTI(TYPE_NAME, BASE_TYPE_NAME)                                                                                   \
public:                                                                                                                        \
    struct StaticTypeDecl                                                                                                      \
    {                                                                                                                          \
        static const TypeId id()                                                                                               \
        {                                                                                                                      \
            return std::type_index(typeid(TYPE_NAME));                                                                         \
        }                                                                                                                      \
        static constexpr const char* name()                                                                                    \
        {                                                                                                                      \
            return #TYPE_NAME;                                                                                                 \
        }                                                                                                                      \
    };                                                                                                                         \
    static const TypeInfo* GetTypeInfoStatic()                                                                                 \
    {                                                                                                                          \
        static TypeInfo staticInfo = reflect::MetaManager::Instance().AddMeta(std::type_index(typeid(TYPE_NAME)), #TYPE_NAME); \
        staticInfo.SetBase(BASE_TYPE_NAME::GetTypeInfoStatic());                                                               \
        return &staticInfo;                                                                                                    \
    }                                                                                                                          \
    virtual const TypeId& GetType() const                                                                                      \
    {                                                                                                                          \
        return TYPE_NAME::GetTypeInfoStatic()->id();                                                                           \
    }                                                                                                                          \
    virtual const std::string GetTypeName() const                                                                              \
    {                                                                                                                          \
        return TYPE_NAME::GetTypeInfoStatic()->name();                                                                         \
    }                                                                                                                          \
    virtual const TypeInfo* GetTypeInfo() const                                                                                \
    {                                                                                                                          \
        return TYPE_NAME::GetTypeInfoStatic();                                                                                 \
    }



// 根据是否有 GetTypeInfoStatic 静态成员判断是否继承至 Object
template <typename T, typename = void>
class InheritFromObject : public std::false_type
{};

template <typename T>
class InheritFromObject<T, std::void_t<typename T::StaticTypeDecl>> : public std::true_type
{};



// Object Factory
class SP_API ObjectFactory : public RefCounted
{
public:
    ObjectFactory(Context* context)
        : context_(context)
    {}
    const reflect::Meta* GetTypeInfo() const { return typeInfo_; }
    const std::string&   GetTypeName() const { return typeInfo_->name(); }
    const TypeId&        GetType() const { return typeInfo_->id(); }
    //virtual std::shared_ptr<Object> CreateObject() = 0;
protected:
    const reflect::Meta* typeInfo_{};   // 它实质上是指向一个静态局部变量
    Context*             context_;
};

template <typename T>
class ObjectFactoryImpl : public ObjectFactory
{
public:
    // 父类的无参数构造函数会隐式调用，但是有参数的构造函数需要显示调用
    ObjectFactoryImpl(Context* context)
        : ObjectFactory(context)
    {
        typeInfo_ = T::GetTypeInfoStatic();
    }
    /*std::shared_ptr<Object> CreateObject()
		{
			return std::make_shared<Object>(new T(context_));
		}*/
};
}   // namespace SPing
