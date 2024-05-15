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
		m_currentState = &LightOff::getInstance();
	}

	void Light::setState(ILightState& newState)
	{
		m_currentState->exit(this);  // do something before we change state
		m_currentState = &newState;  // change state
		m_currentState->enter(this); // do something after we change state
	}

	void Light::toggle()
	{
		// delegate the task of determining the next state to the current state!
		m_currentState->toggle(this);
	}
}

// ===========================================================================
// End-of-File
// ===========================================================================

