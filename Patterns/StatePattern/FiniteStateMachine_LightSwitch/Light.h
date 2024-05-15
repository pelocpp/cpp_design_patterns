// ===========================================================================
// Light.h
// ===========================================================================

#pragma once

#include "LightState.h"

namespace StateMachine
{
	class Light
	{
	public:
		// c'tor
		Light();

		// getter
		ILightState* getCurrentState() const { return m_currentState; }

		// the state transition is delegated to the current state
		void toggle();

		// called by the current state
		void setState(ILightState& newState);

	private:
		ILightState* m_currentState;
	};
}

// ===========================================================================
// End-of-File
// ===========================================================================
