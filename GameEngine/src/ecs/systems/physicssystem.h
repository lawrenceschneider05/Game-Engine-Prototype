#pragma once
#include <ecs/components/componentmanager.h>
#include "glm/glm.hpp"
#include "physics/physics.h"
#include "ecs/components/components.h"
#include "tiles/tilemanager.h"

using namespace glm;

namespace GameEngine
{
	constexpr vec2 GRAVITY_VECTOR = { 0, -9 };

	class PhysicsSystem
	{
	public:
		PhysicsSystem(ComponentManager& _cm, TileManager& _tm) : cm(_cm), tm(_tm) {}
		~PhysicsSystem();
		void init();
		void update(f64 dt);
		void onComponentChanged();
	private:
		ComponentManager& cm;
		TileManager& tm;
		vector<Entity> entities;
		Signature signature;
		vector<PhysicsObject> possibleCollisions;

		inline PhysicsObject physicsObjectFromEntity(Entity e)
		{
			Position& p = *cm.getComponent<Position>(e);
			Size& s = *cm.getComponent<Size>(e);
			Velocity& v = *cm.getComponent<Velocity>(e);
			Acceleration& a = *cm.getComponent<Acceleration>(e);

			return { p.x, p.y, s.w, s.h, v.vx, v.vy, a.ax, a.ay };
		}

		inline void applyPhysicsObject(Entity e, PhysicsObject obj)
		{
			Position& p = *cm.getComponent<Position>(e);
			Size& s = *cm.getComponent<Size>(e);
			Velocity& v = *cm.getComponent<Velocity>(e);
			Acceleration& a = *cm.getComponent<Acceleration>(e);

			p.x = obj.x;
			p.y = obj.y;
			
			s.w = obj.w;
			s.h = obj.h;

			v.vx = obj.vx;
			v.vy = obj.vy;

			a.ax = obj.ax;
			a.ay = obj.ay;
		}
	};
}