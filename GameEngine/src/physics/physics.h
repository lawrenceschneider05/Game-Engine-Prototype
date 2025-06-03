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

		PhysicsObject()
			: x(0), y(0), w(0), h(0), vx(0), vy(0), ax(0), ay(0) {
		}

		PhysicsObject(f32 x, f32 y, f32 w, f32 h,
			f32 vx = 0, f32 vy = 0, f32 ax = 0, f32 ay = 0)
			: x(x), y(y), w(w), h(h), vx(vx), vy(vy), ax(ax), ay(ay) {
		}
	};
	constexpr f32 METER = 64;
	constexpr f32 GRAVITY = METER * 5;
	constexpr f32 TERMINAL_VELOCITY = METER * 100;
	

	class Physics
	{
	public:
		static void applyGravity(PhysicsObject& obj, f64 dt);
		static void processMovement(PhysicsObject& obj, f64 dt);
		static void processCollisions(PhysicsObject& obj, vector<PhysicsObject> objects, f64 dt);
		static void resolveCollision(PhysicsObject& one, PhysicsObject& two, f64 dt);
		static bool isCollision(PhysicsObject one, PhysicsObject two, f64 dt);
	private:
	};
}