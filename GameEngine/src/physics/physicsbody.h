#pragma once
#include "types.h"
namespace GameEngine
{
	constexpr f32 METER = 64;
	constexpr f32 GRAVITY = METER * 9;
	constexpr f32 TERMINAL_VELOCITY = METER * 100;
	struct AABB
	{
		f32 x, y, w, h;
	};



	inline bool AABBIsCollision(AABB a, AABB b)
	{
		return (
			a.x < b.x + b.w &&
			a.x + a.w > b.x &&
			a.y < b.y + b.h &&
			a.y + a.h > b.y
			);
	}
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