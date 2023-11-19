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
		LightOff(const LightOff& other);
		LightOff& operator=(const LightOff& other);
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
		LowIntensity(const LowIntensity& other);
		LowIntensity& operator=(const LowIntensity& other);
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
		MediumIntensity(const MediumIntensity& other);
		MediumIntensity& operator=(const MediumIntensity& other);
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
		HighIntensity(const HighIntensity& other);
		HighIntensity& operator=(const HighIntensity& other);
	};
}

// ===========================================================================
// End-of-File
// ===========================================================================
