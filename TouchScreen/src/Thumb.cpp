#include "Thumb.h"
#include <SDL_image.h>
#include "InputHandler.h"

Thumb::Thumb(float radius)
{
	this->radius = radius;
	joystickRadius = radius * .5f;
}

void Thumb::init(SDL_Renderer* canvas)
{
	this->canvas = canvas;
	if (!loadMedia()) {
		printf("Failed to load Texture");
	}
	int w, h;

	SDL_GetRendererOutputSize(canvas, &w, &h);

	backgroundRect = new SDL_Rect();
	backgroundRect->w = radius * 2;
	backgroundRect->h = radius * 2;
	backgroundRect->x = w / 2 - radius;
	backgroundRect->y = h / 2 - radius;

	joystickRect = new SDL_Rect();
	joystickRect->w = joystickRadius * 2;
	joystickRect->h = joystickRadius * 2;
	joystickRect->x = w / 2 - joystickRadius;
	joystickRect->y = h / 2 - joystickRadius;

	InputHandler::instance().addListener(this);
}

void Thumb::update()
{

}

void Thumb::onMouseButtonHold()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	Vec2 mousePos(mouseX, mouseY);

	int w, h;
	SDL_GetRendererOutputSize(canvas, &w, &h);
	Vec2 center(w / 2, h / 2);

	Vec2 direction = mousePos - center;

	double magnitude = direction.Magnitude();
	if (magnitude > radius)
	{
		double percentage = radius / magnitude;
		direction.x *= percentage;
		direction.y *= percentage;
	}

	joystickRect->x = center.x + direction.x - joystickRadius;
	joystickRect->y = center.y + direction.y - joystickRadius;

	//get Input Vector
	inputVector.x = direction.x / radius;
	inputVector.y = direction.y / radius;
}

void Thumb::onMouseButtonUp()
{
	int w, h;

	SDL_GetRendererOutputSize(canvas, &w, &h);

	joystickRect->x = w / 2 - joystickRadius;
	joystickRect->y = h / 2 - joystickRadius;

	inputVector.x = 0;
	inputVector.y = 0;
}

void Thumb::draw()
{
	SDL_SetTextureAlphaMod(circle, 0x99);
	SDL_RenderCopy(canvas, circle, NULL, backgroundRect);
	SDL_RenderCopy(canvas, circle, NULL, joystickRect);
}

void Thumb::deinit()
{
	SDL_DestroyTexture(circle);
	delete backgroundRect;
	delete joystickRect;

	circle = NULL;
	canvas = NULL;
	backgroundRect = NULL;
	joystickRect = NULL;
}

SDL_Texture* Thumb::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(canvas, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

bool Thumb::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	circle = loadTexture("circle.png");
	if (circle == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}

Vec2 Thumb::getInputVector() const
{
	return inputVector;
}
