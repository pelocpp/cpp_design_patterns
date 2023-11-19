//#include <iostream>
//#include <memory>
//#include <fstream>
//#include <string>
//#include <map>
//
//// #include "LightState.h"
//#include "Light.h"
//
//#include "ConcreteLightStates.h"
//
//// https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/
//
//namespace StateMachine
//{
//
//	//enum class LightState {
//	//	Off,
//	//	Low,
//	//	Medium,
//	//	High
//	//};
//
//	//std::map<LightState, LightState> lightTransitions = {
//	//	{LightState::Off, LightState::Low},
//	//	{LightState::Low, LightState::Medium},
//	//	{LightState::Medium, LightState::High},
//	//	{LightState::High, LightState::Off}
//	//};
//
//
// //   class Light;
//
//	//class LightState
//	//{
//	//public:
//	//	virtual void enter(Light* light) = 0;
//	//	virtual void toggle(Light* light) = 0;
//	//	virtual void exit(Light* light) = 0;
//	//	virtual ~LightState() {}
//	//};
//
//
//	//class LightOff : public LightState
//	//{
//	//public:
//	//	void enter(Light* light) {}
//	//	void toggle(Light* light);
//	//	void exit(Light* light) {}
//	//	static LightState& getInstance();
//
//	//private:
//	//	LightOff() {}
//	//	LightOff(const LightOff& other);
//	//	LightOff& operator=(const LightOff& other);
//	//};
//
//
//
//	//class Light
//	//{
//	//public:
//	//	Light();
//	//	// Same as before
//	//	inline LightState* getCurrentState() const { return currentState; }
//	//	// In here, we'll delegate the state transition to the currentState
//	//	void toggle();
//	//	// This will get called by the current state
//	//	void setState(LightState& newState);
//
//	//private:
//	//	// LightState here is now a class, not the enum that we saw earlier
//	//	LightState* currentState;
//	//};
//
//	//Light::Light()
//	//{
//	//	currentState = &LightOff::getInstance();
//	//}
//
//	//void Light::setState(LightState& newState)
//	//{
//	//	currentState->exit(this);  // do something before we change state
//	//	currentState = &newState;  // change state
//	//	currentState->enter(this); // do something after we change state
//	//}
//
//	//void Light::toggle()
//	//{
//	//	// Delegate the task of determining the next state to the current state!
//	//	currentState->toggle(this);
//	//}
//
//
//
//	//class LowIntensity : public LightState
//	//{
//	//public:
//	//	void enter(Light* light) {}
//	//	void toggle(Light* light);
//	//	void exit(Light* light) {}
//	//	static LightState& getInstance();
//
//	//private:
//	//	LowIntensity() {}
//	//	LowIntensity(const LowIntensity& other);
//	//	LowIntensity& operator=(const LowIntensity& other);
//	//};
//
//	//class MediumIntensity : public LightState
//	//{
//	//public:
//	//	void enter(Light* light) {}
//	//	void toggle(Light* light);
//	//	void exit(Light* light) {}
//	//	static LightState& getInstance();
//
//	//private:
//	//	MediumIntensity() {}
//	//	MediumIntensity(const MediumIntensity& other);
//	//	MediumIntensity& operator=(const MediumIntensity& other);
//	//};
//
//	//class HighIntensity : public LightState
//	//{
//	//public:
//	//	void enter(Light* light) {}
//	//	void toggle(Light* light);
//	//	void exit(Light* light) {}
//	//	static LightState& getInstance();
//
//	//private:
//	//	HighIntensity() {}
//	//	HighIntensity(const HighIntensity& other);
//	//	HighIntensity& operator=(const HighIntensity& other);
//	//};
//
//
//	//void LightOff::toggle(Light* light)
//	//{
//	//	// Off -> Low
//	//	light->setState(LowIntensity::getInstance());
//	//}
//
//	//LightState& LightOff::getInstance()
//	//{
//	//	static LightOff singleton;
//	//	return singleton;
//	//}
//
//	//void LowIntensity::toggle(Light* light)
//	//{
//	//	// Low -> Medium
//	//	light->setState(MediumIntensity::getInstance());
//	//}
//
//	//LightState& LowIntensity::getInstance()
//	//{
//	//	static LowIntensity singleton;
//	//	return singleton;
//	//}
//
//	//void MediumIntensity::toggle(Light* light)
//	//{
//	//	// Medium -> High
//	//	light->setState(HighIntensity::getInstance());
//	//}
//
//	//LightState& MediumIntensity::getInstance()
//	//{
//	//	static MediumIntensity singleton;
//	//	return singleton;
//	//}
//
//	//void HighIntensity::toggle(Light* light)
//	//{
//	//	// High -> Low
//	//	light->setState(LightOff::getInstance());
//	//}
//
//	//LightState& HighIntensity::getInstance()
//	//{
//	//	static HighIntensity singleton;
//	//	return singleton;
//	//}
//
//
//}
//
////void test_state_machine()
////{
////	using namespace StateMachine;
////
////
//////	class LightState;
////
////	Light light; 
////	light.setState(LowIntensity::getInstance());
////	light.setState(HighIntensity::getInstance());
////		
////	light.toggle();
////
////}
//
//// ===========================================================================
//// End-of-File
//// ===========================================================================
