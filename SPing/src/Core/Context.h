#pragma once
#include "Object.h"
#include "SPingPre.h"

namespace SPing
{
	class SP_API Context : public RefCounted
	{
	public:
		Context() {}
		~Context() {}

		void RegisterFactory(std::shared_ptr<ObjectFactory> factory)
		{
			factories[factory->GetType()] = factory;
			std::cout << factory->GetTypeName();
		}

		template <typename T>
		void RegisterFactory()
		{
			std::shared_ptr<ObjectFactory> factory = std::shared_ptr<ObjectFactory>(new ObjectFactoryImpl<T>(this));
			RegisterFactory(factory);
		}
		
	private:
		std::map<StringHash, std::shared_ptr<ObjectFactory>> factories;

	};


}