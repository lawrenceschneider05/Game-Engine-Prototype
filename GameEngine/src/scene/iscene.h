#pragma once
#include "types.h"
#include "rendering/camera.h"
namespace GameEngine
{
	class IScene
	{
	public:
		IScene(Camera& _camera) : camera(_camera)
		{

		}
		virtual void update(f32 dt) = 0;
		virtual void render() = 0;
	protected:
		Camera& camera;
	};
}