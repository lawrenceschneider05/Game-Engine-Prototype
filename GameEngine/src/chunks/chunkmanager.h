#pragma once
#include <vector>
#include "tile.h"
#include "chunk.h"
#include "physics/aabb.h"
#include "chunkserializer.h"
#include "chunkcoordinate.h"

using std::vector;

namespace GameEngine
{
	class ChunkManager
	{
	public:
		ChunkManager();
		~ChunkManager();

		void render();

		inline bool changeInTiles()
		{
			bool b = tilesUpdated;
			tilesUpdated = false;
			return b; 
		}
		vector<AABB> getColliders();
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
