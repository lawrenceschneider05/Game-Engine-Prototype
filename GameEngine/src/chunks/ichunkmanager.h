#pragma once
#include "coordinate.h"

namespace GameEngine
{
	class IChunkManager
	{
	public:
		virtual ~IChunkManager() {};
		virtual bool addBlock(Coordinate position) = 0;
		virtual bool removeBlock(Coordinate position) = 0;
		virtual bool isBlockAt(Coordinate position) = 0;
	};
}