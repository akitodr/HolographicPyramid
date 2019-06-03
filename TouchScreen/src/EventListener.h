#pragma once
#include <SDL.h>
#include "MathVectors.h"

class EventListener
{
private:
public:
	virtual void onMouseButtonDown() {};
	virtual void onMouseButtonHold() {};
	virtual void onMouseButtonUp() {};
	virtual void onMouseMove() {};
	virtual void onMouseWheel() {};

	virtual void onTouchDown(const Vec2& fingerPos) {};
	virtual void onTouchHold(const Vec2& fingerPos) {};
	virtual void onTouchUp(const Vec2& fingerPos) {};
	virtual void onTouchMove(const Vec2& fingerPos) {};
};