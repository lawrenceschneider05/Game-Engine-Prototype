#pragma once
#include "tile.h"
#include "types.h"
#include "chunkcoordinate.h"

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
		Chunk(ChunkCoordinate c);

		TileType getTile(i32 x, i32 y);

		void setTile(i32 x, i32 y, TileType type);

		ChunkCoordinate getCoordinates() { return coordinates; }

		inline vector<Tile> getTiles()
		{
			vector<Tile> t;
			for (int y = 0; y < CHUNK_HEIGHT_TILES; y++)
			{
				for (int x = 0; x < CHUNK_WIDTH_TILES; x++)
				{
					t.push_back(getTileCollider(x, y));
				}
			}
			return t;
		}
		inline u32 indexOf(i32 x, i32 y)
		{
			return y * CHUNK_WIDTH_TILES + x;
		}

		TileType* getTileData() { return tiles.data(); }

		void destroyTile(u32 x, u32 y)
		{
			tiles[indexOf(x, y)] = TILE_EMPTY;
		}
	private:
		ChunkCoordinate coordinates;
		array<TileType, CHUNK_WIDTH_TILES * CHUNK_HEIGHT_TILES> tiles;

		

		inline Tile getTileCollider(i32 x, i32 y)
		{
			f32 tileX = coordinates.x + (x * TILE_WIDTH);
			f32 tileY = coordinates.y + (y * TILE_HEIGHT);
			return { getTile(x, y), tileX, tileY, TILE_WIDTH, TILE_HEIGHT };
		}
	};
}