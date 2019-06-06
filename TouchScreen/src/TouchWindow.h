#include <SDL.h>
#include <SDL_thread.h>
#include "Thumb.h"
#include "ScannedObject.h"
#include "Window.h"
#include "Button.h"


class TouchWindow {

private:
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Renderer* canvas = NULL;
	Thumb* thumb;
	ScannedObject* object;
	SDL_Thread* thread;
	SDL_Rect viewPort;
	SDL_Rect objectRect;
	const char* title;
	Window* projectionWindow;
	Button* rightButton;
	Button* leftButton;
	std::string folders[5];

	int incrementFolder;

public:
	TouchWindow(const char* title);
	TouchWindow();

	void init();

	void loop();

	void close();

	SDL_Renderer* getCanvas() const;
	
	void defViewPort();
	void defFolders();
};