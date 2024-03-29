#pragma once

#include "include.h"
#include "../Events/Event.h"

class Layer {
public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer();

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate() {}
	virtual void OnEvent(Event& event) {}

	inline const std::string& GetName() const { return m_Name; }

protected:
	std::string m_Name;
};