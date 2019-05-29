#include "Window.h"
#include <stdio.h>
#include <SDL_image.h>

Window::Window(const char* title) : title(title) {}

Window::Window() : Window("TouchPad") {}

void Window::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, SDL_WINDOW_FULLSCREEN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create renderer for window
			canvas = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (canvas == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else {

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				}
			}
		}
	}
}

void Window::loop() {
	//Main loop flag
	bool quit = false;

	SDL_Event e;

	button = new Button(1366 / 4, 768 / 4, 1366 / 2, 768 / 2);

	init();
	

	//While application is running
	while (!quit)
	{
		float secs = SDL_GetTicks() / 1000.f;
		
		//F64740
		
		//Clear screen
		SDL_SetRenderDrawColor(canvas, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(canvas);

		button->update();
		button->draw(canvas);

		//Render red filled quad
		/*SDL_Rect fillRect = { 1366 / 4, 768 / 4, 1366 / 2, 768 / 2 };
		SDL_SetRenderDrawColor(canvas, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(canvas, &fillRect);*/

		SDL_RenderPresent(canvas);
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit (inputs)
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

		}
	}
	close();
}

void Window::close() {
	
	//Destroy window
	delete button;
	SDL_DestroyRenderer(canvas);
	SDL_DestroyWindow(window);
	button = NULL;
	canvas = NULL;
	window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Window::getCanvas() const
{
	return canvas;
}
