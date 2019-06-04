#include "InputHandler.h"

InputHandler::InputHandler() 
{
	down = new DownCommand();
	hold = new HoldCommand();
	up = new DropCommand();
	motion = new MotionCommand();
	wheel = new WheelCommand();

	touchDown = new TouchDownCommand();
	touchHold = new TouchHoldCommand();
	touchUp = new TouchUpCommand();
	touchMove = new TouchMoveCommand();
	
	mouseDown = false;
}



void InputHandler::update()
{
	if (mouseDown) {
		hold->execute();
		touchHold->execute();
	}
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

	//TOUCH
	if (event.type == SDL_FINGERDOWN) {
		Vec2 touchPos(event.tfinger.x, event.tfinger.y);
		touchDown->execute(touchPos);
		mouseDown = true;
	}
	else if (event.type == SDL_FINGERUP) {
		Vec2 touchPos(event.tfinger.x, event.tfinger.y);
		touchUp->execute(touchPos);
		mouseDown = false;
	}
	else if (event.type == SDL_FINGERMOTION) { 
		Vec2 touchPos(event.tfinger.x, event.tfinger.y);
		touchMove->execute(touchPos); 
	}

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

	touchDown->addListener(listener);
	touchHold->addListener(listener);
	touchUp->addListener(listener);
	touchMove->addListener(listener);
}


