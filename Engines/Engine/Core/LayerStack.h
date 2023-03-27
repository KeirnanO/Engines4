#pragma once

#include "Layer.h"
#include <vector>

typedef std::vector<Layer*> VectorLayer;

class LayerStack 
{
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Layer* layer);
	void PopLayer(Layer* layer);

	//Overlay

	VectorLayer::iterator begin() { return m_Layers.begin(); }
	VectorLayer::iterator end() { return m_Layers.end(); }
private:
	VectorLayer m_Layers;
	VectorLayer::iterator m_LayerInsert;
};
