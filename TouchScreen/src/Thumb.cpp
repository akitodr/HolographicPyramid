#include "Thumb.h"
#include <SDL_image.h>
#include "InputHandler.h"
#include "ImageLoader.h"

Thumb::Thumb(float radius, const Vec2& pos)
{
	this->radius = radius;
	joystickRadius = radius * .5f;
	position = pos;
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
	backgroundRect->x = position.x - radius;
	backgroundRect->y = position.y - radius;

	joystickRect = new SDL_Rect();
	joystickRect->w = joystickRadius * 2;
	joystickRect->h = joystickRadius * 2;
	joystickRect->x = position.x - joystickRadius;
	joystickRect->y = position.y - joystickRadius;

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

	Vec2 direction = mousePos - position;

	double magnitude = direction.Magnitude();
	if (magnitude > radius)
	{
		double percentage = radius / magnitude;
		direction.x *= percentage;
		direction.y *= percentage;
	}

	joystickRect->x = position.x + direction.x - joystickRadius;
	joystickRect->y = position.y + direction.y - joystickRadius;

	//get Input Vector
	inputVector.x = direction.x / radius;
	inputVector.y = direction.y / radius;
}

void Thumb::onMouseButtonUp()
{
	joystickRect->x = position.x - joystickRadius;
	joystickRect->y = position.y - joystickRadius;

	inputVector.x = 0;
	inputVector.y = 0;
}

void Thumb::onTouchHold(const Vec2& fingerPos)
{
	//Vec2 direction = fingerPos - position;

	//double magnitude = direction.Magnitude();
	//if (magnitude > radius)
	//{
	//	double percentage = radius / magnitude;
	//	direction.x *= percentage;
	//	direction.y *= percentage;
	//}

	//joystickRect->x = position.x + direction.x - joystickRadius;
	//joystickRect->y = position.y + direction.y - joystickRadius;

	////get Input Vector
	//inputVector.x = direction.x / radius;
	//inputVector.y = direction.y / radius;
}

void Thumb::onTouchUp(const Vec2& fingerPos)
{
	/*int w, h;

	SDL_GetRendererOutputSize(canvas, &w, &h);

	joystickRect->x = position.x - joystickRadius;
	joystickRect->y = position.y - joystickRadius;

	inputVector.x = 0;
	inputVector.y = 0;*/
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

bool Thumb::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	circle = loadTexture(canvas, "circle.png");
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
