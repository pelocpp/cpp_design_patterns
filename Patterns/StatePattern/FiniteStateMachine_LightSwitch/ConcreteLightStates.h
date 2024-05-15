// ===========================================================================
// ConcreteLightStates.h
// ===========================================================================

#pragma once

#include <iostream>

#include "Light.h"

namespace StateMachine
{
	class LightOff : public ILightState
	{
	public:
		void enter(Light* light) {
			std::cout << "entering state LightOff" << std::endl;
		}

		void toggle(Light* light);

		void exit(Light* light) {
			std::cout << "exiting  state LightOff" << std::endl;
		}

		static ILightState& getInstance();

	private:
		LightOff() {}
	};

	// -----------------------------------------------------------

	class LowIntensity : public ILightState
	{
	public:
		void enter(Light* light) {
			std::cout << "entering state LowIntensity" << std::endl;
		}

		void toggle(Light* light);

		void exit(Light* light) {
			std::cout << "exiting  state LowIntensity" << std::endl;
		}

		static ILightState& getInstance();

	private:
		LowIntensity() {}
	};

	// -----------------------------------------------------------

	class MediumIntensity : public ILightState
	{
	public:
		void enter(Light* light) {
			std::cout << "entering state MediumIntensity" << std::endl;
		}

		void toggle(Light* light);

		void exit(Light* light) {
			std::cout << "exiting  state MediumIntensity" << std::endl;
		}

		static ILightState& getInstance();

	private:
		MediumIntensity() {}
	};

	// -----------------------------------------------------------

	class HighIntensity : public ILightState
	{
	public:
		void enter(Light* light) {
			std::cout << "entering state HighIntensity" << std::endl;
		}

		void toggle(Light* light);

		void exit(Light* light) {
			std::cout << "exiting  state HighIntensity" << std::endl;
		}

		static ILightState& getInstance();

	private:
		HighIntensity() {}
	};
}

// ===========================================================================
// End-of-File
// ===========================================================================
