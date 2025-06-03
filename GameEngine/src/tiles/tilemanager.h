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

		Chunk getChunk()
		{
			return testingChunk;
		}
	private:
		void renderTile(TileType, f32, f32);
		Chunk testingChunk;
	};
}