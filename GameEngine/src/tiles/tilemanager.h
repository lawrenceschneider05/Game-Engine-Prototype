#pragma once
#include <vector>
#include "tile.h"
#include "chunk.h"

using std::vector;

namespace GameEngine
{
	class TileManager
	{
	public:
		TileManager();
		~TileManager();

		void render();

		inline Chunk getChunk()
		{
			return testingChunk;
		}

		inline bool changeInTiles()
		{
			bool b = tilesUpdated;
			tilesUpdated = false;
			return b; 
		}
	private:
		vector<Chunk> chunks{};
		void renderTile(TileType, f32, f32);
		Chunk testingChunk;

		bool tilesUpdated = false;
		
		void addTile(TileType, f32, f32);
	};
}