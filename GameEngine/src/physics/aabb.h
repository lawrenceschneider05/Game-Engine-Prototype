#pragma once
#include "types.h"
namespace GameEngine
{
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

	inline bool AABBContainsPoint(const AABB& a, f32 x, f32 y)
	{
		return (x >= a.x) && (x <= a.x + a.w) &&
			(y >= a.y) && (y <= a.y + a.h);
	}
}