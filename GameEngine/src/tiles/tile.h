#pragma once
#include "types.h"

namespace GameEngine
{
	enum TileType
	{
		TILE_EMPTY,
		TILE_GRASS
	};

	constexpr u32 TILE_WIDTH = 16;
	constexpr u32 TILE_HEIGHT = TILE_WIDTH;

	struct Tile
	{
		TileType type;
		f32 w, h;
	};
}