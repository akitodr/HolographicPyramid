#include <SDL.h>
#include "Command.h"
#include <vector>
#include "MathVectors.h"

class InputHandler {
private:
	Command* down;
	Command* hold;
	Command* up;
	Command* motion;
	Command* wheel;

	Command* touchDown;
	Command* touchHold;
	Command* touchUp;
	Command* touchMove;

	Vec2 thumbPosition;

	bool mouseDown;

	InputHandler();

public:
	void update();
	void handleInput(const SDL_Event& event);
	static InputHandler& instance();

	void addListener(EventListener *listener);
};