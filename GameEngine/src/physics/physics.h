#pragma once
#include "types.h"
#include <vector>

using std::vector;

namespace GameEngine
{
	struct PhysicsObject
	{
		f32 x, y, w, h;
		f32 vx, vy, ax, ay;
	};
	constexpr f32 GRAVITY = 100;

	class Physics
	{
	public:
		static void applyGravity(PhysicsObject& obj, f64 dt);
		static void processMovement(PhysicsObject& obj, f64 dt);
		static void processCollisions(PhysicsObject& obj, vector<PhysicsObject> objects, f64 dt);
		static void resolveCollision(PhysicsObject& one, PhysicsObject& two, f64 dt);
	private:
	};
}