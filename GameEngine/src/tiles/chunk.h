#pragma once
#include "tile.h"
#include "types.h"
#include <array>
#include <vector>
#include <memory>

using std::unique_ptr;
using std::vector;
using std::array;

namespace GameEngine
{
	constexpr u32 CHUNK_WIDTH_TILES = 16;
	constexpr u32 CHUNK_HEIGHT_TILES = 16;

	constexpr u32 CHUNK_WIDTH_PIXELS = CHUNK_WIDTH_TILES * TILE_WIDTH;
	constexpr u32 CHUNK_HEIGHT_PIXELS = CHUNK_HEIGHT_TILES * TILE_HEIGHT;

	class Chunk
	{
	public:
		Chunk(i32 x, i32 y);

		TileType getTile(u32 x, u32 y);

		void setTile(u32 x, u32 y, TileType type);

		inline i32 getX() { return chunkX; }
		inline i32 getY() { return chunkY; }

	private:
		i32 chunkX, chunkY;
		array<TileType, CHUNK_WIDTH_TILES * CHUNK_HEIGHT_TILES> tiles;

		inline u32 indexOf(u32 x, u32 y)
		{
			return y * CHUNK_HEIGHT_TILES + x;
		}
	};
}