#include <iostream>
#include "EventListener.h"
#include <vector>

class Command {
protected: 
	std::vector<EventListener*> listeners;
public:
	virtual ~Command() {}
	virtual void execute() = 0;

	void addListener(EventListener* listener)
	{
		listeners.push_back(listener);
	}
};

//SDL_FINGERMOTION, SDL_FINGERDOWN, or SDL_FINGERUP

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