#pragma once
#include <vector>
#include <cmath>

#include "tile.h"
#include "chunk.h"
#include "physics/aabb.h"
#include "chunkserializer.h"
#include "chunkcoordinate.h"
#include "log/logger.h"

using std::vector;

namespace GameEngine
{
	class ChunkManager
	{
	public:
		ChunkManager();
		~ChunkManager();

		void update();
		void render();

		inline bool areChunksUpdated()
		{
			bool b = chunksUpdated;
			chunksUpdated = false;
			return b;
		}
		vector<AABB> getColliders();

		void click(f32 x, f32 y)
		{
			Chunk* c = getChunkAt(x, y);
			if (!c) { return; }
			unloadChunk(c);
		}
	private:
		void unloadChunk(Chunk* c)
		{
			//c->clearTiles();
			
			serializer.saveChunk(c);
			chunks.erase(std::remove(chunks.begin(), chunks.end(), c), chunks.end());
			
			delete c;
			c = nullptr;
			updateColliders();
			chunksUpdated = true;
		}
		void loadChunks();

		void renderChunk(Chunk* c);
		void renderTile(TileType, f32 x, f32 y);

		void addTile(Chunk* c, TileType, i32 x, i32 y);

		void addChunk(ChunkCoordinate coords)
		{
			Chunk* c = new Chunk(coords);

			for (int y = 0; y < CHUNK_HEIGHT_TILES; y++)
			{
				for (int x = 0; x < CHUNK_WIDTH_TILES; x++)
				{
					addTile(c, TILE_GRASS, x, y);

				}
			}
			chunks.push_back(c);
			Logger::log(LOG_SUCCESS, "chunk added");
			serializer.saveChunk(c);
			updateColliders();
		}
		Chunk* getChunkAt(f32 x, f32 y)
		{
			
			for (Chunk* c : chunks)
			{
				if (c->getChunkCoordinates() == chunkCoordinateAt(x, y))
				{
					return c;
				}
			}
			return nullptr;
		}
		inline ChunkCoordinate chunkCoordinateAt(f32 x, f32 y)
		{
			return {
				static_cast<i32>(std::floor(x / CHUNK_WIDTH_PIXELS)),
				static_cast<i32>(std::floor(y / CHUNK_HEIGHT_PIXELS))
			};
		}
		void updateColliders();
	private:
		ChunkSerializer serializer;

		vector<Chunk*> chunks{};
		vector<AABB> colliders{};


		bool chunksUpdated = false;

		
	};
}
