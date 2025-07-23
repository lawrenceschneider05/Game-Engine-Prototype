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
	constexpr i32 CHUNK_WIDTH_TILES = 16;
	constexpr i32 CHUNK_HEIGHT_TILES = 16;

	constexpr f32 CHUNK_WIDTH_PIXELS = CHUNK_WIDTH_TILES * TILE_WIDTH;
	constexpr f32 CHUNK_HEIGHT_PIXELS = CHUNK_HEIGHT_TILES * TILE_HEIGHT;

	class Chunk
	{
	public:
		Chunk(i32 x, i32 y);

		TileType getTile(u32 x, u32 y);

		void setTile(u32 x, u32 y, TileType type);

		inline f32 getX() { return chunkX; }
		inline f32 getY() { return chunkY; }

		inline vector<Tile> getTiles()
		{
			vector<Tile> tiles;
			for (int y = 0; y < CHUNK_HEIGHT_TILES; y++)
			{
				for (int x = 0; x < CHUNK_WIDTH_TILES; x++)
				{
					tiles.push_back(getTileCollider(x, y));
				}
			}
			return tiles;
		}
		inline u32 indexOf(u32 x, u32 y)
		{
			return y * CHUNK_HEIGHT_TILES + x;
		}
	private:
		f32 chunkX, chunkY;
		array<TileType, CHUNK_WIDTH_TILES * CHUNK_HEIGHT_TILES> tiles;

		

		inline Tile getTileCollider(f32 x, f32 y)
		{
			f32 tileX = chunkX + (x * TILE_WIDTH);
			f32 tileY = chunkY + (y * TILE_HEIGHT);
			return { getTile(x, y), tileX, tileY, TILE_WIDTH, TILE_HEIGHT };
		}
	};
}