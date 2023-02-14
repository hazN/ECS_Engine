#pragma once

#include "Event.h"
#include "KeyCodes.h"
#include <string>
#include <sstream>

namespace sas
{
	// KeyEvents
	// This will be the parent class to all the Key related events
	class KeyEvent : public Event
	{
	public:
		inline KeyCode GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(KeyCode keycode)
			: m_KeyCode(keycode) {}
		KeyCode m_KeyCode;
	};

	// When a key is pressed
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		// Get how many times the Key was Repeated
		inline int GetRepeatCount() const { return m_RepeatCount; }

		// To be used in printing statements
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << (uint16_t)m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	// When a key is released
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << (int)m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	// When a character is typed
	// This is different from key pressed as 
	// it checks the key to be lowerscale or upperscale
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << (int)m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}