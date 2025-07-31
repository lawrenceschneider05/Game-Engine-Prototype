#pragma once
#include <vector>
#include <array>

#include "coordinate.h"
#include "tile.h"
#include "types.h"
#include "physics/aabb.h"

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
		Chunk(Coordinate _worldPosition, ChunkCoordinate _chunkPosition);

		void addBlock(Coordinate pos);
		void removeBlock(Coordinate pos);
		bool isBlockAt(const Coordinate& pos);

		void setBlock(u32 position)
		{
			addBlock(chunkPosToWorldPos(position));
		}

		const Coordinate& getWorldCoordinates() { return worldPosition; }
		const ChunkCoordinate& getChunkCoordinates() { return chunkPosition; }

		bool isDirty();

		vector<AABB>& getColliders();

		array<TileType, CHUNK_WIDTH_TILES* CHUNK_HEIGHT_TILES>& getTileData();

		TileType getTileAt(Coordinate worldPosition);

		void generateColliders();

	private:
		u32 worldPosToChunkPos(Coordinate worldPos);
		Coordinate chunkPosToWorldPos(u32 chunkPos);
		AABB tileToAABB(u32 tile);
		void addCollider(u32 tile);
		void addCollider(Coordinate worldPos);
		void removeCollider(u32 tile);
		void removeCollider(Coordinate worldPos);
	private:
		array<TileType, CHUNK_WIDTH_TILES * CHUNK_HEIGHT_TILES> tileData{};
		vector<AABB> colliders{};
		Coordinate worldPosition{};
		ChunkCoordinate chunkPosition{};
		bool dirty = false;
	};
}
