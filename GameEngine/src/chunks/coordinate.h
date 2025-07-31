#pragma once
#include "types.h"
#include <functional>  // for std::hash
#include <cstddef>     // for std::size_t

namespace GameEngine
{
	// (0,0) = chunk with bottom left on origin of screen
	struct ChunkCoordinate
	{
		i32 x, y;

		bool operator == (const ChunkCoordinate& other) const
		{
			return x == other.x && y == other.y;
		}
	};
	struct Coordinate
	{
		f32 x, y;

		bool operator==(const Coordinate& other) const
		{
			return x == other.x && y == other.y;
		}
	};
}

namespace std {
	template<>
	struct hash<GameEngine::ChunkCoordinate> {
		std::size_t operator()(const GameEngine::ChunkCoordinate& coord) const noexcept {
			std::size_t h1 = std::hash<int>{}(coord.x);
			std::size_t h2 = std::hash<int>{}(coord.y);
			return h1 ^ (h2 << 1);
		}
	};
}