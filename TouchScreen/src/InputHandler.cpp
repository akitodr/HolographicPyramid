#include "InputHandler.h"

InputHandler::InputHandler() 
{
	down = new DownCommand();
	hold = new HoldCommand();
	up = new DropCommand();
	motion = new MotionCommand();
	wheel = new WheelCommand();
	
	mouseDown = false;
}



void InputHandler::update()
{
	if (mouseDown)
		hold->execute();
}

void InputHandler::handleInput(const SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) 
	{ 
		down->execute(); 
		mouseDown = true;
	}
	else if (event.type == SDL_MOUSEBUTTONUP) 
	{ 
		up->execute(); 
		mouseDown = false;
	}
	else if (event.type == SDL_MOUSEMOTION) { motion->execute(); }
	else if (event.type == SDL_MOUSEWHEEL) { wheel->execute(); }
}

InputHandler& InputHandler::instance() {
	static InputHandler inputHandler;
	return inputHandler;
}

void InputHandler::addListener(EventListener* listener)
{
	down->addListener(listener);
	hold->addListener(listener);
	up->addListener(listener);
	motion->addListener(listener);
	wheel->addListener(listener);
}


