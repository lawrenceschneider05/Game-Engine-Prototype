#pragma once
#include <vector>

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

		inline bool changeInTiles()
		{
			bool b = tilesUpdated;
			tilesUpdated = false;
			return b; 
		}
		vector<AABB> getColliders();

		void click(f32 x, f32 y)
		{
			f32 chunkX = x / CHUNK_WIDTH_PIXELS;
			f32 chunkY = y / CHUNK_HEIGHT_PIXELS;
			ChunkCoordinate cords{ chunkX, chunkY };
			for (Chunk* c : chunks)
			{
				if (c->getCoordinates() == cords)
				{
					Logger::log(LOG_DEBUG, cords.y);
					delete c;
					c = nullptr;
					return;
				}
			}
			getTile(x, y);
		}

		void getTile(f32 x, f32 y)
		{
			// find onscreen chunks
			// determine which of those it is in
			// find tile at that x and y
			f32 chunkX = x / CHUNK_WIDTH_PIXELS;
			f32 chunkY = y / CHUNK_HEIGHT_PIXELS;
			Logger::log(LOG_DEBUG, chunkX);

		}
	private:
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
			serializer.saveChunk(c);
		}
	private:
		ChunkSerializer serializer;

		vector<Chunk*> chunks{};
		

		bool tilesUpdated = false;
		
		
	};
}
