#include "entityfactory.h"
#include "ecs/components/components.h"
using std::make_unique;
namespace GameEngine
{
	EntityFactory::EntityFactory()
	{

	}

	unique_ptr<ECSManager> EntityFactory::init()
	{
		auto ecs = make_unique<ECSManager>();
		ecs->init();
		initPlayer(ecs);
		

		return ecs;
	}

	void EntityFactory::initPlayer(unique_ptr<ECSManager>& ecs)
	{
		Entity player = ecs->addEntity();
		ecs->addComponent<Position>(player, { 0,0 });
		ecs->addComponent<Size>(player, { 64, 64 });
		ecs->addComponent<Velocity>(player, { 10,0 });
		ecs->addComponent<Acceleration>(player, { 0,0 });
		Color c = { 210 / 255.0, 175 / 255.0, 111 / 255.0, 1.0f };
		ecs->addComponent<Color>(player, c);
	}

	
}
