#include <SDL.h>
#include "Thumb.h"
#include <string>

class Window {

private:
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Renderer* canvas = NULL;
	Thumb* thumb;
	const char* title;


public:
	Window(const char* title);
	Window();

	void init();

	void loop();

	void close();

	SDL_Renderer* getCanvas() const;
	
	
};