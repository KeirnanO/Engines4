#pragma once

#include "Event.h"
//#include <sstream>

class KeyEvent : public Event {
public:
	inline int GetKeyCode() const { return m_KeyCode; }
		
	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	KeyEvent(int keyCode) 
		: m_KeyCode(keyCode) {}

	int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent {
public:
	KeyPressedEvent(int keyCode)
		: KeyEvent(keyCode) {}

	//std::string ToString() const override

	EVENT_CLASS_TYPE(KeyPressed);
};

class KeyReleasedEvent : public KeyEvent {
public:
	KeyReleasedEvent(int keyCode)
		: KeyEvent(keyCode) {}

	//std::string ToString() const override

	EVENT_CLASS_TYPE(KeyReleased);
};

