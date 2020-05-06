#ifndef SP_LAYER_H
#define SP_LAYER_H

#include "Events/Event.h"

namespace SPing {

	class SP_API Layer {

	public:
		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return _DebugName; }

	protected:
		std::string _DebugName;

	};


}








#endif
