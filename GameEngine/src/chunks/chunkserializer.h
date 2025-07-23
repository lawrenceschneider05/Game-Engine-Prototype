#pragma once
#include <string>
#include "chunk.h"
#include "types.h"
#include <vector>

using std::vector;
using std::string;

struct ChunkCoordinate
{
	i32 x, y;
};

namespace GameEngine
{
	class ChunkSerializer
	{
	public:
		ChunkSerializer();
		~ChunkSerializer();
		Chunk* loadChunk(i32 x, i32 y);
		void saveChunk(Chunk* chunk);
	private:
		void loadCoordinates();
		void saveCoordinates();
	private:
		vector<ChunkCoordinate> coordinates;
		const string directory = "game_data/world_data/chunk_data/";
		const string coordinatesFileName = "ChunkCoordinates.bin";
	};
}
