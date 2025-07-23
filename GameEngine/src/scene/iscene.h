#pragma once
#include "types.h"
namespace GameEngine
{
	class IScene
	{
	public:
		IScene()
		{

		}
		virtual void update(f32 dt) = 0;
		virtual void render() = 0;
	private:
		
	};
}