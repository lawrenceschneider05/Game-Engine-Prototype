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
	private:
		void renderTile(TileType, u32, u32);

		Chunk testingChunk;
	};
}