#include <SDL.h>
#include "Command.h"
#include <vector>

class InputHandler {
private:
	Command* down;
	Command* hold;
	Command* up;
	Command* motion;
	Command* wheel;

	bool mouseDown;

	InputHandler();

public:
	void update();
	void handleInput(const SDL_Event& event);
	static InputHandler& instance();

	void addListener(EventListener *listener);
};