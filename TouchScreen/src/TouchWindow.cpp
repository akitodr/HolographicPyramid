#include "TouchWindow.h"
#include <stdio.h>
#include <SDL_image.h>
#include "InputHandler.h"


TouchWindow::TouchWindow(const char* title) : title(title) {}

TouchWindow::TouchWindow() : TouchWindow("TouchPad") {}

int runProjectionWindow(void * data)
{
	((Window*)data)->update();
	return 0;
}

void TouchWindow::init()
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
		window = SDL_CreateWindow(title, 0, 0, 1920, 1080, SDL_WINDOW_BORDERLESS);
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

	incrementFolder = 0;
	defFolders();

	int w, h;
	SDL_GetRendererOutputSize(canvas, &w, &h);

	std::string path = folders[incrementFolder];
	thumb = new Thumb(300, Vec2((w * 0.5) + 450, (h * 0.5)));
	thumb->init(canvas);
	object = new ScannedObject(canvas);
	object->setupImages(path);
	object->init();
	
	projectionWindow = new Window();
	projectionWindow->init();
	projectionWindow->setThumb(thumb);
	projectionWindow->setObjectPath(path);
	

	defViewPort();
	
	rightButton = new Button(canvas, 0, 0, 100, 100, true);
	rightButton->init();
	rightButton->setPosition(Vec2((viewPort.x + viewPort.w) - rightButton->getTextureSize().x, viewPort.y));

	leftButton = new Button(canvas, viewPort.x, viewPort.y, 100, 100, false);
	leftButton->init();

}

void TouchWindow::loop() {
	//Main loop flag
	bool quit = false;

	SDL_Event e;

	init();

	float animationDelay = 5, delayCounter = 0;

	float time = SDL_GetTicks();

	//While application is running
	while (!quit)
	{
		float secs = (SDL_GetTicks() - time) / 1000;
		time = SDL_GetTicks();

		thread = SDL_CreateThread(runProjectionWindow, "Projection Window", projectionWindow);

		InputHandler::instance().update();

		//F64740
		SDL_SetRenderDrawColor(canvas, 0x00, 0x00, 0x00, 0xFF);
		//Clear screen
		SDL_RenderClear(canvas);

		thumb->update();

		SDL_RenderSetViewport(canvas, &viewPort);
		Vec2 inputVector = Vec2(thumb->getInputVector().x, -thumb->getInputVector().y);
		if (inputVector.x == 0 && inputVector.y == 0) {
			delayCounter += secs;
		}
		else {
			object->incrementAngle(Vec2(thumb->getInputVector().x, -thumb->getInputVector().y) * 100 * secs);
			delayCounter = 0;
		}

		if (delayCounter >= animationDelay) {
			object->incrementAngle(Vec2(0.5, 0) * 100 * secs);
		}
		object->update(secs);
		//object->draw();

		SDL_RenderCopy(canvas, object->getCurrentTexture(), NULL, &objectRect);
		SDL_SetRenderDrawColor(canvas, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(canvas, NULL);

		SDL_RenderSetViewport(canvas, NULL);
		thumb->draw();

		rightButton->draw();
		leftButton->draw();

		rightButton->update();
		leftButton->update();

		SDL_RenderPresent(canvas);

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit (inputs)
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			InputHandler::instance().handleInput(e);
		}

		if (rightButton->isClicked()) {
			std::cout << "Clicked Right" << std::endl;

			incrementFolder++;
			if (incrementFolder > 4)
				incrementFolder = 0;

			object->setupImages(folders[incrementFolder]);
			//SDL_WaitThread(thread, NULL);
			projectionWindow->setObjectPath(folders[incrementFolder]);
		}

		if (leftButton->isClicked()) {
			std::cout << "Clicked Left" << std::endl;

			incrementFolder--;
			if (incrementFolder < 0)
				incrementFolder = 4;

			object->setupImages(folders[incrementFolder]);
			//SDL_WaitThread(thread, NULL);
			projectionWindow->setObjectPath(folders[incrementFolder]);
		}

		SDL_WaitThread(thread, NULL);
	}

	SDL_WaitThread(thread, NULL);
	thumb->deinit();
	object->deinit();
	projectionWindow->close();
	close();
}

void TouchWindow::close() {

	//Destroy window
	SDL_DestroyRenderer(canvas);
	SDL_DestroyWindow(window);
	delete object;
	delete thumb;
	delete object;
	delete projectionWindow;
	delete rightButton;
	delete leftButton;
	canvas = NULL;
	window = NULL;
	thumb = NULL;
	object = NULL;
	projectionWindow = NULL;
	rightButton = NULL;
	leftButton = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* TouchWindow::getCanvas() const
{
	return canvas;
}

void TouchWindow::defViewPort()
{
	int w, h;
	SDL_GetRendererOutputSize(canvas, &w, &h);
	viewPort.w = w * 0.4;
	viewPort.h = h * 0.9;
	viewPort.x = (h - viewPort.h) * 0.5;
	viewPort.y = (h - viewPort.h) * 0.5;

	int imgW, imgH;
	SDL_QueryTexture(object->getCurrentTexture(), NULL, NULL, &imgW, &imgH);

	float proportion = imgW / imgH;

	objectRect.w = viewPort.w;
	objectRect.h = objectRect.w * (imgH / imgW);
	objectRect.y = viewPort.h / 2 - objectRect.h / 2;

}

void TouchWindow::defFolders()
{
	folders[0] = "vader\\";
	folders[1] = "cranio\\";
	folders[2] = "testa\\";
	folders[3] = "meio\\";
	folders[4] = "maxilar\\";
}
