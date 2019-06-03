#include <iostream>
#include "EventListener.h"
#include <vector>
#include "MathVectors.h"

class Command {
protected: 
	std::vector<EventListener*> listeners;
public:
	virtual ~Command() {}
	virtual void execute() {};
	virtual void execute(const Vec2& fingerPos) {};

	void addListener(EventListener* listener)
	{
		listeners.push_back(listener);
	}
};

//SDL_FINGERMOTION, SDL_FINGERDOWN, or SDL_FINGERUP

class TouchDownCommand : public Command {
public:
	virtual void execute(const Vec2& fingerPos) {
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onTouchDown(fingerPos);
		}
	}
};

class TouchHoldCommand : public Command {
public:
	virtual void execute(const Vec2& fingerPos) {
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onTouchHold(fingerPos);
		}
	}
};

class TouchUpCommand : public Command {
public:
	virtual void execute(const Vec2& fingerPos) {
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onTouchUp(fingerPos);
		}
	}
};

class TouchMoveCommand : public Command {
public:
	virtual void execute(const Vec2& fingerPos) {
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onTouchMove(fingerPos);
		}
	}
};

class DownCommand : public Command
{
public:
	virtual void execute() {
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onMouseButtonDown();
		}
	}
};

class HoldCommand : public Command {

public:
	virtual void execute() {
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onMouseButtonHold();
		}
	}
};

class DropCommand : public Command {

public:
	virtual void execute() {
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onMouseButtonUp();
		}
	}
};

class MotionCommand : public Command {

public:
	virtual void execute() {
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onMouseMove();
		}
	}
};

class WheelCommand : public Command {

public:
	virtual void execute() {
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onMouseWheel();
		}
	}
};