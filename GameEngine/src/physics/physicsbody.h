#pragma once
#include "types.h"
#include "aabb.h"
namespace GameEngine
{
	
	
	struct Motion
	{
		f32 vx, vy, ax, ay;
	};
	class PhysicsBody
	{
	public:
		PhysicsBody(AABB _aabb, bool _gravity, bool _isStatic) : aabb(_aabb),
			motion({ 0,0,0,0 }), isStatic(_isStatic), gravity(_gravity)
		{ }

		inline AABB desiredPosition(f32 dt)
		{
			f32 newVx = motion.vx + (motion.ax * dt);
			f32 newVy = motion.vy + (motion.ay * dt);
			f32 newX = aabb.x + (newVx * dt);
			f32 newY = aabb.y + (newVy * dt);
			return { newX, newY, aabb.w, aabb.h };
		}

		AABB aabb;
		Motion motion;
		bool isStatic;
		bool gravity;
		bool grounded = false;
	};
}