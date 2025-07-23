#include "chunkserializer.h"

#include <sstream>
#include <fstream>
#include <iostream>

using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::ios;

namespace GameEngine
{
	ChunkSerializer::ChunkSerializer()
	{
		loadCoordinates();
	}

	ChunkSerializer::~ChunkSerializer()
	{
		saveCoordinates();
	}
	Chunk* ChunkSerializer::loadChunk(i32 x, i32 y)
	{
		stringstream fileName;
		fileName << directory << x << "_" << x << ".bin";

		ifstream in(fileName.str(), ios::in | ios::binary);

		i32 count = 16 * 16;

		Chunk* chunk = new Chunk(x, y);
		in.read(reinterpret_cast<char*>(chunk->getTiles().data()), count * sizeof(Tile));
		in.close();
		return chunk;
	}
	void ChunkSerializer::saveChunk(Chunk* chunk)
	{
		coordinates.push_back({ chunk->getX(), chunk->getY() });

		stringstream fileName;
		fileName << directory << chunk->getX() << "_" << chunk->getY() << ".bin";
		ofstream out(fileName.str(), ios::out | ios::binary);
		f32 count = chunk->getTiles().size();
		out.write(reinterpret_cast<const char*>(chunk->getTiles().data()), count * sizeof(Tile));
		out.close();
	}

	void ChunkSerializer::loadCoordinates()
	{
		stringstream fileName;
		fileName << directory << coordinatesFileName;

		ifstream in(fileName.str(), ios::in | ios::binary);

		i32 count;
		in.read(reinterpret_cast<char*>(&count), sizeof(count));

		for (int i = 0; i < count; i++)
		{
			in.read(reinterpret_cast<char*>(coordinates.data()), count * sizeof(ChunkCoordinate));
		}
		in.close();
	}

	void ChunkSerializer::saveCoordinates()
	{
		stringstream fileName;
		fileName << directory << coordinatesFileName;

		ofstream out(fileName.str(), ios::out | ios::binary);

		out.write(reinterpret_cast<const char*>(coordinates.data()), coordinates.size() * sizeof(ChunkCoordinate));
	}
}