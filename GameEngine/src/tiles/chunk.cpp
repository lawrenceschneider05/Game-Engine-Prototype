#include "chunk.h"
using std::fill;

namespace GameEngine
{
	Chunk::Chunk()
	{
		tiles = {TileType::TILE_EMPTY};
		fill(tiles.begin(), tiles.end(), TileType::TILE_EMPTY);
	}
	TileType Chunk::getTile(u32 x, u32 y)
	{
		return tiles[indexOf(x, y)];
	}

	void Chunk::setTile(u32 x, u32 y, TileType t)
	{
		tiles[indexOf(x, y)] = t;
	}
}