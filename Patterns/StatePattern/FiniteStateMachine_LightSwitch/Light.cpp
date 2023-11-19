// ===========================================================================
// LightState.cpp
// ===========================================================================

#include "Light.h"
#include "ConcreteLightStates.h"

namespace StateMachine
{
	Light::Light()
	{
		// set the initial state
		currentState = &LightOff::getInstance();
	}

	void Light::setState(ILightState& newState)
	{
		currentState->exit(this);  // do something before we change state
		currentState = &newState;  // change state
		currentState->enter(this); // do something after we change state
	}

	void Light::toggle()
	{
		// delegate the task of determining the next state to the current state!
		currentState->toggle(this);
	}
}

// ===========================================================================
// End-of-File
// ===========================================================================

