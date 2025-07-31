#pragma once
#include "chunks/coordinate.h"
#include "chunks/chunkmanager.h"
#include "rendering/camera.h"

namespace GameEngine
{
	class IWorld
	{
	public:
		IWorld(Camera* _camera) : camera(_camera)
		{

		}
		
		virtual void update(f32 dt) = 0;
		virtual void render() = 0;

	public:
		IChunkManager* chunkManager;
		Camera* camera;
	};
}