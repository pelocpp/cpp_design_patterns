// ===========================================================================
// LightState.h
// ===========================================================================

#pragma once

namespace StateMachine
{
	// forward declaration needed
	class Light;

	class ILightState
	{
	public:
		virtual ~ILightState() {}

		virtual void enter (Light* light) = 0;
		virtual void toggle (Light* light) = 0;
		virtual void exit (Light* light) = 0;
	};
}

// ===========================================================================
// End-of-File
// ===========================================================================
