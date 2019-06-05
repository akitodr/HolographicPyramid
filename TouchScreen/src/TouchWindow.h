#include <SDL.h>
#include <SDL_thread.h>
#include "Thumb.h"
#include "ScannedObject.h"
#include "Window.h"


class TouchWindow {

private:
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Renderer* canvas = NULL;
	Thumb* thumb;
	ScannedObject* object;
	SDL_Thread* thread;
	const char* title;


public:
	TouchWindow(const char* title);
	TouchWindow();

	void init();

	void loop();

	void close();

	SDL_Renderer* getCanvas() const;

	ScannedObject* getActualObject();

};