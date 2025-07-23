#pragma once
#include <vector>
#include "tile.h"
#include "chunk.h"
#include "physics/aabb.h"

using std::vector;

namespace GameEngine
{
	class TileManager
	{
	public:
		TileManager();
		~TileManager();

		void render();

		inline bool changeInTiles()
		{
			bool b = tilesUpdated;
			tilesUpdated = false;
			return b; 
		}
		vector<AABB> getColliders();
	private:
		vector<Chunk*> chunks{};
		void renderChunk(Chunk* c);
		void renderTile(TileType, f32, f32);

		bool tilesUpdated = false;
		
		void addTile(Chunk* c, TileType, f32, f32);

		void addChunk(f32 x, f32 y)
		{
			Chunk* c = new Chunk(x, y);
			for (int y = 0; y < CHUNK_HEIGHT_TILES; y++)
			{
				for (int x = 0; x < CHUNK_WIDTH_TILES; x++)
				{
					addTile(c, TILE_GRASS, x, y);
				}
			}
			chunks.push_back(c);
		}
	};
}