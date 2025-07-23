#pragma once
#include "ientity.h"
#include "physics/physicsbody.h"
namespace GameEngine
{
	class IActor : public IEntity
	{
	public:
		IActor(bool hasGravity, f32 x, f32 y, f32 w, f32 h) : pb({x,y,w,h}, hasGravity, false)
		{

		}
		PhysicsBody& getPhysicsBody()
		{
			return pb;
		}
	protected:
		f32 x() { return pb.aabb.x; }
		f32 y() { return pb.aabb.y; }
		f32 w() { return pb.aabb.w; }
		f32 h() { return pb.aabb.h; }
		f32 vx() { return pb.motion.vx; }
		f32 vy() { return pb.motion.vy; }
		f32 ax() { return pb.motion.ax; }
		f32 ay() { return pb.motion.ay; }

		void applyHorizontalVelocity(f32 v) { pb.motion.vx += v; }
		void applyVerticalVelocity(f32 v) { pb.motion.vy += v; }
		void applyHorizontalAcceleration(f32 v) { pb.motion.ax += v; }
		void applyVerticalAcceleration(f32 v) { pb.motion.ay += v; }
		

		void setHorizontalVelocity(f32 v) { pb.motion.vx = v; }
		void setVerticalVelocity(f32 v) { pb.motion.vy = v; }
		void setHorizontalAcceleration(f32 v) { pb.motion.ax = v; }
		void setVerticalAcceleration(f32 v) { pb.motion.ay = v; }

		bool grounded() { return pb.grounded; }

	private:
		PhysicsBody pb;
	};
}