#include <SDL.h>
#include "ScannedObject.h"
#include "Thumb.h"

class Window {

private:
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Renderer* canvas = NULL;
	SDL_Rect rect;
	SDL_Point pivot;
	ScannedObject* object;
	Thumb* thumb;
	const char* title;
	float time;

	float animationDelay = 5, delayCounter = 0;

public:
	Window(const char* title);
	Window();

	void init();

	void loop();

	void update();

	void close();

	SDL_Renderer* getCanvas() const;

	void setupRect();

	void setThumb(Thumb* thumb);

	void setObjectPath(std::string path);
};