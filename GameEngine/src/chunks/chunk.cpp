#include "chunk.h"
using std::fill;

namespace GameEngine
{
	Chunk::Chunk(ChunkCoordinate coords) : coordinates(coords)
	{
		fill(tiles.begin(), tiles.end(), TileType::TILE_EMPTY);
	}
	TileType Chunk::getTile(i32 x, i32 y)
	{
		return tiles[indexOf(x, y)];
	}

	void Chunk::setTile(i32 x, i32 y, TileType t)
	{
		tiles[indexOf(x, y)] = t;
	}
}