#pragma once

#include "tahm/seek.h"
/*
		tahmlib
		A C++ library for Game Development

		Author: Tamta Asatiani
		tamta@geolab.edu.ge

		-- Methods --

		Main library methods that represent the game loop:
		start, update, render, and event.
*/
extern Tahm& tahm;

#if __has_include("main.h")

#include "main.h"
#define GAME_FOUND 1

#else

#define GAME_FOUND 0

#endif