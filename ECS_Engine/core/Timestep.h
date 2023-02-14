#pragma once

namespace sas
{
	// hold the time flow of the game
	class Timestep
	{
	public:
		Timestep(float time = 0.f)
			:m_Time(time)
		{

		}

		// Get time in seconds
		float GetSeconds() const { return m_Time; }

		// Get time in milliseconds
		float GetMilliseconds() const { return m_Time * 1000.f; }

		// to use the object directly in float's operation
		operator float() { return m_Time; }

	private:
		float m_Time;
	};
}