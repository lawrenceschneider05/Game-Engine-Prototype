#pragma once
#include "types.h"

namespace GameEngine
{
	// (0,0) = chunk with bottom left on origin of screen
	struct ChunkCoordinate
	{
		i32 x, y;
	};
	struct Coordinate
	{
		f32 x, y;

		bool operator==(const Coordinate& other) const {
			return x == other.x && y == other.y;
		}
	};
}