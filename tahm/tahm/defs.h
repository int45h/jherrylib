#pragma once

/*
		tahmlib
		A C++ library for Game Development

		Author: Tamta Asatiani
		tamta@geolab.edu.ge

		-- Macros --

		Macros used by tahmlib.
*/
#define Rect SDL_Rect

#define Color SDL_Color

#define Event SDL_Event
#define QUIT SDL_QUIT

#define keyName key.keysym.sym

#define TahmSound Tahm::Audio::Sound

#include <stdlib.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;
typedef size_t usize;
typedef ssize_t ssize;