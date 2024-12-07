#include "seek.h"

/*
	tahmlib
	A C++ library for Game Development

	Author: Tamta Asatiani
	tamta@geolab.edu.ge

	-- Graphics --

	Definitions for all graphics related methods,
	such as: font and shape rendering, setting the draw color,
    background fill.
*/
Tahm::Graphics::Graphics(Renderer& renderer)
{
	this->renderer = &renderer;

	font = new Font();
	draw = new Draw(renderer);
}

Tahm::Graphics::~Graphics()
{
	delete font;
	delete draw;
}

void Tahm::Graphics::clear(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(this->renderer->SDLrenderer, r, g, b, a);
	SDL_RenderClear(this->renderer->SDLrenderer);
}

void Tahm::Graphics::setColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(this->renderer->SDLrenderer, r, g, b, a);

	// convert to char
	unsigned char cr = r, cg = g, cb = b, ca = a;
	color = { cr, cg, cb , ca};
}

void Tahm::Graphics::renderText(int x, int y, TTF_Font* font, const char* text)
{
	SDL_Surface* renderedText = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->SDLrenderer, renderedText);

	SDL_Rect destination = { x, y, renderedText->w, renderedText->h };
	SDL_RenderCopy(renderer->SDLrenderer, texture, NULL, &destination);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(renderedText);
}

void Tahm::Graphics::renderText(const char* alignment, int alignmentWidth, int marginX, int marginY, TTF_Font* font, const char* text)
{
	SDL_Surface* renderedText = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->SDLrenderer, renderedText);

	SDL_Rect destination;

	if (compareStrings(alignment, "left"))
	{
		destination = { marginX, marginY, renderedText->w, renderedText->h };
	}
	else if (compareStrings(alignment, "center"))
	{
		destination = { alignmentWidth / 2 - renderedText->w / 2 + marginX, marginY, renderedText->w, renderedText->h };
	}
	else if (compareStrings(alignment, "right"))
	{
		destination = { alignmentWidth - renderedText->w + marginX, marginY, renderedText->w, renderedText->h };
	}
	else
	{
		std::cerr << "Invalid alignment!" << '\n';
	}

	int res = SDL_RenderCopy(renderer->SDLrenderer, texture, NULL, &destination);
    if (res != 0)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
    }

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(renderedText);
}

//draw
Tahm::Graphics::Draw::Draw(Renderer& renderer)
{
	this->renderer = &renderer;
}

SDL_Rect Tahm::Graphics::Draw::rect(int x, int y, int width, int height)
{
	SDL_Rect rectangle;

	rectangle.x = x;
	rectangle.y = y;

	rectangle.w = width;
	rectangle.h = height;

	SDL_RenderDrawRect(this->renderer->SDLrenderer, &rectangle);
	SDL_RenderFillRect(this->renderer->SDLrenderer, &rectangle);

	return rectangle;
}