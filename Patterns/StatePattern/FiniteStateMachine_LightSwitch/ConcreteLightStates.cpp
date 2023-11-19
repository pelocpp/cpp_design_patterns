// ===========================================================================
// ConcreteLightStates.cpp
// ===========================================================================

#pragma once

#include "Light.h"

#include "ConcreteLightStates.h"

namespace StateMachine
{
	void LightOff::toggle(Light* light)
	{
		// Off -> Low
		light->setState(LowIntensity::getInstance());
	}

	ILightState& LightOff::getInstance()
	{
		static LightOff singleton;
		return singleton;
	}

	// -----------------------------------------------------------

	void LowIntensity::toggle(Light* light)
	{
		// Low -> Medium
		light->setState(MediumIntensity::getInstance());
	}

	ILightState& LowIntensity::getInstance()
	{
		static LowIntensity singleton;
		return singleton;
	}

	// -----------------------------------------------------------

	void MediumIntensity::toggle(Light* light)
	{
		// Medium -> High
		light->setState(HighIntensity::getInstance());
	}

	ILightState& MediumIntensity::getInstance()
	{
		static MediumIntensity singleton;
		return singleton;
	}

	// -----------------------------------------------------------

	void HighIntensity::toggle(Light* light)
	{
		// High -> Low
		light->setState(LightOff::getInstance());
	}

	ILightState& HighIntensity::getInstance()
	{
		static HighIntensity singleton;
		return singleton;
	}
}

// ===========================================================================
// End-of-File
// ===========================================================================
