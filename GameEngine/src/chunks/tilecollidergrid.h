#pragma once
#include <vector>
#include "tile.h"

using std::vector;

namespace GameEngine
{
	class TileColliderGrid
	{
	public:
		TileColliderGrid();
	private:
		vector<Tile> tileColliders;
	};
}