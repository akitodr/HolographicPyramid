#pragma once
#include <SDL.h>

class EventListener
{
private:
public:
	virtual void onMouseButtonDown() {};
	virtual void onMouseButtonHold() {};
	virtual void onMouseButtonUp() {};
	virtual void onMouseMove() {};
	virtual void onMouseWheel() {};
};