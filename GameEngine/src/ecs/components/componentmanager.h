#pragma once
#include "ecs/entities/entity.h"
#include "componentarray.h"
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "componentregistry.h"
#include "log/logger.h"
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>

using std::unordered_map;
using std::type_index;
using std::unique_ptr;
using std::vector;

using std::to_string;
using std::make_unique;

namespace GameEngine
{

	class ComponentManager
	{
	public:
		ComponentManager()
		{

		}
		template <typename T>
		Signature registerComponentType()
		{
			type_index i = type_index(typeid(T));

			Signature s = cr.registerComponent<T>();
			// std::cout << typeid(T).name() << << " " << cr.getComponentSignature<T>() << "\n";

			if (componentArrays.find(i) == componentArrays.end()) {
				componentArrays[i] = std::make_unique<ComponentArray<T>>();
			}

			return s;
		}

		template <typename T> 
		void addComponent(Entity e, const T& c)
		{
			getComponentArray<T>().addComponent(e, c);
			entityBitmasks[e] |= cr.getComponentSignature<T>();
		}

		template <typename T>
		T* getComponent(Entity e)
		{
			return getComponentArray<T>().getComponent(e);
		}

		template <typename T>
		void removeComponent(Entity e)
		{
			getComponentArray<T>().removeComponent(e);
			entityBitmasks[e] &= ~cr.getComponentSignature<T>();
		}

		template <typename T>
		bool hasComponent(Entity e)
		{
			return getComponentArray<T>().hasComponent(e);
		}

		Signature getEntityBitmask(Entity e)
		{
			return entityBitmasks[e];
		}

		vector<Entity> getFilteredEntities(Signature bitmask)
		{
			vector<Entity> entities{};
			for (Entity e = 0; e < entityBitmasks.size(); e++)
			{
				if ((bitmask & entityBitmasks[e]) == bitmask)
				{
					entities.push_back(e);
				}
			}
			return entities;
		}

	private:
		template <typename T>
		ComponentArray<T>& getComponentArray()
		{
			type_index i = type_index(typeid(T));
			if (componentArrays.find(i) == componentArrays.end())
			{
				componentArrays[i] = make_unique<ComponentArray<T>>();
			}

			return *static_cast<ComponentArray<T>*>(componentArrays[i].get());
		}

		unordered_map<type_index, unique_ptr<IComponentArray>> componentArrays;
		ComponentRegistry cr;
		unordered_map<Entity, Signature> entityBitmasks{};
	};
}