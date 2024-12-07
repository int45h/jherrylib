#include "tahm.h"

/*
		tahmlib
		A C++ library for Game Development

		Author: Tamta Asatiani
		tamta@geolab.edu.ge

		-- Tahm --

		Definitions for the main tahmlib methods:
		setup, initialization, cleanup.
*/

Tahm* Tahm::tahm;

void Tahm::init(void)
{
	window.init();
	renderer.init();
	audio.setupDevice();
}

bool Tahm::loadPlugin(const char *path)
{
    if (!script.LoadSharedObject(path)) return false;
    if (!script.Bind(this)) return false;

    return true;
}

Tahm& Tahm::getInstance(void)
{
	if (tahm == nullptr) {
		tahm = new Tahm();
	}
	return *tahm;
}

void Tahm::handleEvents()
{
	Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			break;


		case SDL_KEYDOWN:
			script.RunKeyPressed(event);
			break;

		default:
			break;
		}
	}

}

void Tahm::setup()
{
	script.RunStart();
	init();
}

void Tahm::loop()
{
	handleEvents();

	script.RunUpdate(SDL_GetTicks() / 1000.0f);
	renderer.prepare();

	script.RunDraw();
	renderer.present();

	SDL_Delay(16);
}

void Tahm::run()
{
	setup();

	while (running)
	{
		loop();
	}

	destroy();

	return;
}

void Tahm::destroy(void)
{
    script.Close();
	SDL_DestroyRenderer(renderer.SDLrenderer);
	SDL_DestroyWindow(window.SDLwindow);

	SDL_Quit();
}

Tahm::~Tahm()
{
	//delete window;
	//delete renderer;
	//delete input; 
	//delete graphics;
	//delete audio;
	//delete tahm;
}