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
		ILightState* getCurrentState() const { return currentState; }

		// the state transition is delegated to the current state
		void toggle();

		// called by the current state
		void setState(ILightState& newState);

	private:
		ILightState* currentState;
	};
}

// ===========================================================================
// End-of-File
// ===========================================================================
