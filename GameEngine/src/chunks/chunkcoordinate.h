#pragma once
#include "types.h"

namespace GameEngine
{
	struct ChunkCoordinate
	{
		i32 x, y;

		bool operator==(const ChunkCoordinate& other) const {
			return x == other.x && y == other.y;
		}
	};

	struct WorldCoordinate
	{
		f32 x, y;

		bool operator==(const WorldCoordinate& other) const {
			return x == other.x && y == other.y;
		}
	};
}