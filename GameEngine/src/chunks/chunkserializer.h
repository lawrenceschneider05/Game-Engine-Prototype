#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "chunk.h"
#include "types.h"
#include "chunkcoordinate.h"


using std::vector;
using std::string;



namespace GameEngine
{
	class ChunkSerializer
	{
	public:
		ChunkSerializer();
		~ChunkSerializer();
		Chunk* loadChunk(ChunkCoordinate c);
		void saveChunk(Chunk* chunk);
		vector<ChunkCoordinate> getCoordinates() { return coordinates; }
	private:
		void loadCoordinates();
		void saveCoordinates();

		inline bool chunkExists(const ChunkCoordinate& c)
		{
			return std::find(coordinates.begin(), coordinates.end(), c) != coordinates.end();
		}
	private:
		vector<ChunkCoordinate> coordinates{};
		const string directory = "game_data/world_data/chunk_data/";
		const string coordinatesFileName = "ChunkCoordinates.bin";
	};
}
