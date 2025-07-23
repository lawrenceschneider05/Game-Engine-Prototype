#pragma once
#include "types.h"
namespace GameEngine
{
	class IEntity
	{
	public:
		virtual void update() = 0;
		virtual void render() = 0;
	};
}