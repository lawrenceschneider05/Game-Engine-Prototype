#include "chunkserializer.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::ios;

namespace GameEngine
{
	ChunkSerializer::ChunkSerializer()
	{
		std::filesystem::create_directories("game_data/world_data/chunk_data/");
		loadCoordinates();
	}

	ChunkSerializer::~ChunkSerializer()
	{
		saveCoordinates();
	}

	Chunk* ChunkSerializer::loadChunk(ChunkCoordinate c)
	{
		stringstream fileName;
		fileName << directory << c.x << "_" << c.y << ".bin";

		ifstream in(fileName.str(), ios::in | ios::binary);
		if (!in) {
			std::cerr << "Failed to open chunk file: " << fileName.str() << "\n";
			return nullptr;
		}
		if (in.peek() == std::ifstream::traits_type::eof())
		{
			return nullptr;
		}



		Chunk* chunk = new Chunk(c);
		i32 count = 16 * 16;
		in.read(reinterpret_cast<char*>(chunk->getTileData()), count * sizeof(TileType));
		in.close();
		//std::cout << "tile size: " << chunk->getTiles()[0].type << "\n";
		return chunk;
	}
	void ChunkSerializer::unloadChunk(Chunk* chunk)
	{
		if (!chunk) { return; }
		if (!chunkExists(chunk->getChunkCoordinates()))
		{
			coordinates.push_back({ chunk->getChunkCoordinates() });
			//std::cout << "Coordsinates size: " << coordinates.size() << "\n";
		}
		

		stringstream fileName;
		fileName << directory << chunk->getChunkCoordinates().x << "_" << chunk->getChunkCoordinates().y << ".bin";
		ofstream out(fileName.str(), ios::out | ios::binary);

		if (!out) {
			std::cerr << "Failed to open file for writing: " << fileName.str() << "\n";
			return;
		}
		i32 count = 256;
		out.write(reinterpret_cast<char*>(chunk->getTileData()), count * sizeof(TileType));
		out.close();
	}

	void ChunkSerializer::loadCoordinates()
	{
		stringstream fileName;
		fileName << directory << coordinatesFileName;

		ifstream in(fileName.str(), ios::in | ios::binary);
		if (!in) {
			std::cerr << "Failed to open chunk file: " << fileName.str() << "\n";
			return;
		}
		if (in.peek() == std::ifstream::traits_type::eof())
		{
			return;
		}
		i32 count;
		in.read(reinterpret_cast<char*>(&count), sizeof(count));

		coordinates.resize(count);

		in.read(reinterpret_cast<char*>(coordinates.data()), count * sizeof(ChunkCoordinate));

		in.close();
		std::cout << "Load coordinates coordinates size size: " << count << "\n";
	}

	void ChunkSerializer::saveCoordinates()
	{
		stringstream fileName;
		fileName << directory << coordinatesFileName;

		ofstream out(fileName.str(), ios::out | ios::binary);

		if (!out)
		{
			std::cerr << "Failed to open coordinate file: " << fileName.str() << "\n";
			return;
		}
		i32 count = coordinates.size();
		std::cout << "Save Coordinates coordinates size: " << count << "\n";
		out.write(reinterpret_cast<char*>(&count), sizeof(count));
		out.write(reinterpret_cast<char*>(coordinates.data()), count * sizeof(ChunkCoordinate));
	}
}