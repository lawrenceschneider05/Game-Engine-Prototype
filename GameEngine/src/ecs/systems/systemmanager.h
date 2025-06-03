#pragma once
#include <vector>
#include <memory>
#include "types.h"
#include "ecs/components/componentmanager.h"
#include "physicssystem.h"
#include "rendersystem.h"
#include "tiles/tilemanager.h"
#include "inputsystem.h"


using std::vector;

using std::unique_ptr;
using std::move;
using std::make_unique;

namespace GameEngine
{

	class SystemManager
	{
	public:
		SystemManager(ComponentManager& cm, TileManager& tm) : ps(cm, tm), rs(cm), is(cm)
		{

		}

		void init()
		{
			//systemArray.emplace_back((ISystem*)(new PhysicsSystem(cm)));
			ps.init();
			rs.init();
			is.init();
		}
		inline void update(f64 dt)
		{
			/*for (auto& s : systemArray)
			{
				s->update(dt);
			}*/
			is.update(dt);
			ps.update(dt);
		}
		inline void render()
		{
			/*for (auto& s : systemArray)
			{
				s->render();
			}*/
			rs.render();
		}
		void onComponentChange()
		{
			/*for (auto& s : systemArray)
			{
				s->onComponentChanged();
			}*/
			ps.onComponentChanged();
			rs.onComponentChanged();
			is.onComponentChanged();
		}
	private:
		PhysicsSystem ps;
		RenderSystem rs;
		InputSystem is;
	};
}