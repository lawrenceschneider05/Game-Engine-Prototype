#pragma once
#include "chunks/chunkcoordinate.h"

namespace GameEngine
{
	class IWorld
	{
	public:
		virtual ~IWorld() = 0;
		virtual bool breakBlock(WorldCoordinate pos) = 0;
		virtual bool isBlockAt(WorldCoordinate pos) = 0;
		virtual bool placeBlock(WorldCoordinate pos) = 0;
	};
}