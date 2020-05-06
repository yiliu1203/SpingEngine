#include "SPingPre.h"
#include "LayerStack.h"

namespace SPing {

	LayerStack::LayerStack() {
		firstOverLayerIter = _Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : _Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		firstOverLayerIter = _Layers.emplace(firstOverLayerIter, layer);
		firstOverLayerIter++;
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = find(_Layers.begin(), _Layers.end(), layer);


		if (it != _Layers.end())
		{
			if (firstOverLayerIter == it)
			{
				firstOverLayerIter = _Layers.erase(it);
			}
			else if(firstOverLayerIter < it)
			{
				auto tmpIt = _Layers.erase(it);
			}
			else
			{
				auto tmpIt = _Layers.erase(it);
				auto tmpFirstOverLayerIter = firstOverLayerIter;
				firstOverLayerIter = _Layers.end();

				for (auto newIt = tmpIt; newIt != _Layers.end(); newIt++)
				{
					if (*newIt == *tmpFirstOverLayerIter)
					{
						firstOverLayerIter = newIt;
						break;
					}
				}

			}
		}
	}

	void LayerStack::popOverlay(Layer* layer)
	{
		PopLayer(layer);
	}




}
