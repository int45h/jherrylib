#include "seek.h"

/*
        tahmlib
        A C++ library for Game Development

        Author: Tamta Asatiani
        tamta@geolab.edu.ge

        -- Window --

        Definitions for all methods
        used by the library to set up and configure
        the game window.
*/

void Tahm::Window::create(const char* title, int _width, int _height)
{
    this->title = title;
    this->width = _width;
    this->height = _height;
    
    //if (this->width != _width || this->height != _height)
    //{
    //    SDL_SetWindowSize(SDLwindow, width, height);
    //    this->width = _width;
    //    this->height = _height;    
    //}
}

void Tahm::Window::init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << '\n';
        exit(1);
    }

    SDLwindow = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //x and y
        width, height,
        flags);

    if (!SDLwindow)
    {
        std::cerr << "Failed to open " << width << " x " << height << " window: " << SDL_GetError() << '\n';
        exit(1);
    }
}
