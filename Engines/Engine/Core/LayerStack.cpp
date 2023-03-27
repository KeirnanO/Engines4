#include "Layer.h"
#include "LayerStack.h"

LayerStack::LayerStack()
{
	m_LayerInsert = m_Layers.begin();
}

LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
		delete layer;
}

void LayerStack::PushLayer(Layer* layer)
{
	m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
}

void LayerStack::PopLayer(Layer* layer)
{
	auto iterator = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if (iterator != m_Layers.end()) {
		m_Layers.erase(iterator);
		m_LayerInsert--;
	}
}
