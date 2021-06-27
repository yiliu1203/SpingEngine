#pragma once
#include "SPingPre.h"
#include "Object.h"

namespace SPing
{
	class Context;

	class ComponentBase : public Object
	{
		TYPE_RTTI(ComponentBase, Object);

	public:
		ComponentBase(Context* context) : Object(context)
		{

		}
	};
}