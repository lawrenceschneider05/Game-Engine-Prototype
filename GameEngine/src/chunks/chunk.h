#pragma once
#include <vector>

#include "coordinate.h"
#include "tile.h"
#include "types.h"
#include "physics/aabb.h"

using std::vector;

namespace GameEngine
{
	constexpr i32 CHUNK_WIDTH_TILES = 16;
	constexpr i32 CHUNK_HEIGHT_TILES = 16;

	constexpr f32 CHUNK_WIDTH_PIXELS = CHUNK_WIDTH_TILES * TILE_WIDTH;
	constexpr f32 CHUNK_HEIGHT_PIXELS = CHUNK_HEIGHT_TILES * TILE_HEIGHT;

	class Chunk
	{
	public:
		Chunk(Coordinate _worldPosition, ChunkCoordinate _chunkPosition);

		void addBlock(Coordinate pos);
		void removeBlock(Coordinate pos);
		bool isBlockAt(Coordinate pos);

		const Coordinate& getCoordinates() { return worldPosition; }

		bool isDirty();

		vector<AABB> getColliders();
	private:
		u32 worldPosToChunkPos(Coordinate worldPos);
		Coordinate chunkPosToWorldPos(u32 chunkPos);
		AABB tileToAABB(u32 tile);
		void addCollider(u32 tile);
		void addCollider(Coordinate worldPos);
		void removeCollider(u32 tile);
		void removeCollider(Coordinate worldPos);
	private:
		vector<TileType> tileData{};
		vector<AABB> colliders{};
		Coordinate worldPosition{};
		ChunkCoordinate chunkPosition{};
		bool dirty = false;
	};
}


//#pragma once
//#include "tile.h"
//#include "types.h"
//#include "chunkcoordinate.h"
//#include "physics/aabb.h"
//#include "log/logger.h"
//
//#include <array>
//#include <vector>
//#include <memory>
//
//using std::unique_ptr;
//using std::vector;
//using std::array;
//
//namespace GameEngine
//{
//	constexpr i32 CHUNK_WIDTH_TILES = 16;
//	constexpr i32 CHUNK_HEIGHT_TILES = 16;
//
//	constexpr f32 CHUNK_WIDTH_PIXELS = CHUNK_WIDTH_TILES * TILE_WIDTH;
//	constexpr f32 CHUNK_HEIGHT_PIXELS = CHUNK_HEIGHT_TILES * TILE_HEIGHT;
//
//	class Chunk
//	{
//	public:
//		Chunk(ChunkCoordinate c);
//
//		TileType getTile(i32 x, i32 y);
//
//		void setTile(i32 x, i32 y, TileType type);
//
//		inline ChunkCoordinate getChunkCoordinates() { return coordinates; }
//
//		inline WorldCoordinate getWorldCoordinates()
//		{
//			return { coordinates.x * CHUNK_WIDTH_PIXELS, coordinates.y * CHUNK_HEIGHT_PIXELS };
//		}
//		inline vector<Tile> getTiles()
//		{
//			vector<Tile> t;
//			for (int y = 0; y < CHUNK_HEIGHT_TILES; y++)
//			{
//				for (int x = 0; x < CHUNK_WIDTH_TILES; x++)
//				{
//					t.push_back(getTileCollider(x, y));
//				}
//			}
//			return t;
//		}
//		inline u32 indexOf(i32 x, i32 y)
//		{
//			return y * CHUNK_WIDTH_TILES + x;
//		}
//
//		TileType* getTileData() { return tiles.data(); }
//
//		void destroyTileChunkPosition(u32 x, u32 y)
//		{
//			tiles[indexOf(x, y)] = TILE_EMPTY;
//		}
//		
//		void destroyTileWorldPosition(f32 x, f32 y)
//		{
//			
//			if (AABBContainsPoint(chunkBounds(), x, y))
//			{
//				
//				f32 newX = x - getWorldCoordinates().x;
//				f32 newY = y - getWorldCoordinates().y;
//
//				i32 chunkX = newX / CHUNK_WIDTH_TILES;
//				i32 chunkY = newY / CHUNK_HEIGHT_TILES;
//				Logger::log(LOG_DEBUG, chunkX);
//				destroyTileChunkPosition(chunkX, chunkY);
//			}
//		}
//		
//
//		void clearTiles()
//		{
//			tiles.fill(TILE_EMPTY);
//		}
//
//		
//	private:
//		ChunkCoordinate coordinates;
//		array<TileType, CHUNK_WIDTH_TILES * CHUNK_HEIGHT_TILES> tiles;
//
//		AABB chunkBounds()
//		{
//			AABB a;
//			ChunkCoordinate c = getChunkCoordinates();
//			a.x = c.x * CHUNK_WIDTH_PIXELS;
//			a.y = c.y * CHUNK_WIDTH_PIXELS;
//			a.w = CHUNK_WIDTH_PIXELS;
//			a.h = CHUNK_HEIGHT_PIXELS;
//
//			return a;
//		}
//
//		inline Tile getTileCollider(i32 x, i32 y)
//		{
//			f32 tileX = coordinates.x * CHUNK_WIDTH_PIXELS + x * TILE_WIDTH;
//			f32 tileY = coordinates.y * CHUNK_HEIGHT_PIXELS + y * TILE_HEIGHT;
//			return { getTile(x, y), tileX, tileY, TILE_WIDTH, TILE_HEIGHT };
//		}
//	};
//}