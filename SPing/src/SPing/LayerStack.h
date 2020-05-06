#ifndef SP_LAYERSTACK_H
#define SP_LAYERSTACK_H

#include "Layer.h"
#include <vector>


namespace SPing
{
	class SP_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void popOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return _Layers.begin(); }
		std::vector<Layer*>::iterator end() { return _Layers.end(); }

	
	private:
		std::vector<Layer*> _Layers;
		std::vector<Layer*>::iterator firstOverLayerIter;


	};
}

#endif
