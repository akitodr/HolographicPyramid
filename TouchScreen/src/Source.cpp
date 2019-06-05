#include "TouchWindow.h"
#include <SDL_thread.h>

//int runWindow(void* ptr) {
//	Window* window = new Window();
//	window->loop();
//
//	return 0;
//}

int main(int argc, char* args[])
{
	
	//SDL_Thread* thread = SDL_CreateThread(runWindow, "darthloop", (void *)NULL);

	TouchWindow* touchWindow = new TouchWindow();
	touchWindow->loop();
	//SDL_WaitThread(thread, NULL);

	return 0;
}
