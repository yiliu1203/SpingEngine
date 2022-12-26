#pragma once
#include "SPingPre.h"
#include "StringHash.h"

namespace SPing {

	class Context;

	class SP_API TypeInfo
	{
	public:
		TypeInfo(const std::string& typeName, const TypeInfo* baseTypeInfo) : typeName_(typeName), baseTypeInfo_(baseTypeInfo), type_(StringHash(typeName)) {
		}
		~TypeInfo() = default;
		const std::string& GetTypeName() const { return typeName_; }
		const StringHash& GetType() const { return type_; }
		const TypeInfo* getBaseTypeInfo() const { return baseTypeInfo_; }

		bool IsTypeOf(const StringHash& type) const
		{
			if (type_ == type) return true;
			const TypeInfo* base = getBaseTypeInfo();
			while (base != nullptr)
			{
				if (base->GetType() == type) return true;
				base = base->getBaseTypeInfo();
			}
			return false;
		};

		bool IsTypeOf(const std::string& typeName) const
		{
			if (typeName_ == typeName) return true;
			const TypeInfo* base = getBaseTypeInfo();
			while (base != nullptr) {
				if (base->GetTypeName() == typeName) return true;
				base = base->getBaseTypeInfo();
			}
			return false;
		}

	private:
		std::string typeName_;
		const StringHash type_;
		const TypeInfo* baseTypeInfo_;

	};

	/// <summary>
	/// 这个结构是弱引用的基础，当还存在弱引用时，弱引用还可以访问计数器
	/// 计数器对象还没有释放，但是外层的object对象已经释放了，
	/// </summary>
	struct SP_API RefCount{
		int refs_;
		int weakRefs_;
		RefCount(): refs_(0), weakRefs_(0) {};
		~RefCount() 
		{
			refs_ = -1;
			weakRefs_ = -1;
		}

	};

	class SP_API RefCounted
	{
	public:
		RefCounted() : refCount_(new RefCount()) {
			refCount_->weakRefs_ = 1;
		};

		virtual ~RefCounted()
		{
			assert(refCount_->refs_ == 0);
			assert(refCount_->weakRefs_ >= 1);

			refCount_->refs_ = -1; // 让其他非法访问的时候触发 asset
			// 这里很关键，这个对象如果还有弱引用，则还是可以访问弱引用计数器的
			// 这个对象本身不能再访问计数器
			if (--refCount_->weakRefs_ == 0) {
				delete refCount_;
			}
			refCount_ = nullptr;
		};

		RefCounted(RefCounted& r) = delete;
		RefCounted& operator = (RefCounted& r) = delete;
		void AddRef()
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
		int Refs() const
		{
			return refCount_->refs_;
		};
		int WeakRefs() const
		{
			return refCount_->weakRefs_;
		};

	private:
		RefCount* refCount_;
	};

	
	class SP_API Object : public RefCounted
	{
	public:
		Object(Context* context){
			context_ = context;
		}
		virtual ~Object() {};

		static const TypeInfo* GetTypeInfoStatic() { return nullptr; }
		virtual const StringHash& GetType() const = 0;
		virtual const std::string GetTypeName() const = 0;
		virtual const TypeInfo* GetTypeInfo() const = 0;
		bool IsInstanceOf(const StringHash& type) const { return this->GetTypeInfo()->IsTypeOf(type); }
		bool IsInstanceOf(const TypeInfo* typeInfo) const { return this->GetTypeInfo()->IsTypeOf(typeInfo->GetType()); }

		template <typename T>
		bool IsInstanceOf() const { return IsInstanceOf(T::GetTypeInfoStatic()); }

	private:
		Context* context_;

	};


#define TYPE_RTTI(TYPE_NAME, BASE_TYPE_NAME) \
    public: \
        static const TypeInfo* GetTypeInfoStatic() { static const TypeInfo staticInfo(#TYPE_NAME, BASE_TYPE_NAME::GetTypeInfoStatic()); return &staticInfo;}\
        virtual const StringHash& GetType() const { return TYPE_NAME::GetTypeInfoStatic()->GetType();} \
        virtual const std::string GetTypeName() const { return TYPE_NAME::GetTypeInfoStatic()->GetTypeName();} \
        virtual const TypeInfo* GetTypeInfo() const { return TYPE_NAME::GetTypeInfoStatic();}\



	// Object Factory
	class SP_API ObjectFactory : public RefCounted
	{
	public:
		ObjectFactory(Context* context) : context_(context) {}
		const TypeInfo* GetTypeInfo() const { return typeInfo_; }
		const std::string GetTypeName() const { return typeInfo_->GetTypeName(); }
		const StringHash& GetType() const { return typeInfo_->GetType(); }
		//virtual std::shared_ptr<Object> CreateObject() = 0;
	protected:
		const TypeInfo* typeInfo_{};  // 它实质上是指向一个静态局部变量
		Context* context_;
	};

	template <typename T>
	class ObjectFactoryImpl : public ObjectFactory
	{
	public:
		// 父类的无参数构造函数会隐式调用，但是有参数的构造函数需要显示调用
		ObjectFactoryImpl(Context* context): ObjectFactory(context)
		{
			typeInfo_ = T::GetTypeInfoStatic();
		}
		/*std::shared_ptr<Object> CreateObject()
		{
			return std::make_shared<Object>(new T(context_));
		}*/
	};

	

}

