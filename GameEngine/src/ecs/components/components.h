#pragma once
#include "types.h"

namespace GameEngine
{
	struct Position
	{
		f32 x, y;
	};

	struct Size
	{
		f32 w, h;
	};

	struct Velocity
	{
		f32 vx, vy;
	};

	struct Acceleration
	{
		f32 ax, ay;
	};

	struct Tag
	{
		const char* tag;
	};

	struct Color
	{
		i8 r, g, b, a;
	};

	struct Script
	{
		bool run;
	};
}