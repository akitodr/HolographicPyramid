#include <SDL.h>
#include "Thumb.h"
#include <string>
#include "ScannedObject.h"

class TouchWindow {

private:
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Renderer* canvas = NULL;
	Thumb* thumb;
	ScannedObject* object;
	const char* title;


public:
	TouchWindow(const char* title);
	TouchWindow();

	void init();

	void loop();

	void close();

	SDL_Renderer* getCanvas() const;
};