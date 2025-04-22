#pragma once
#include <unordered_map>
#include <typeindex>
#include "signatures.h"
#include <stdexcept>

using std::unordered_map;
using std::type_index;

namespace GameEngine
{
	class ComponentRegistry
	{
	public:
		ComponentRegistry() : nextSignature(0) {}

		template<typename T>
		Signature registerComponent()
		{
			type_index type = typeid(T);
			if (registry.find(type) == registry.end())
			{
				if (nextSignature >= sizeof(Signature) * 8)
				{
					throw std::runtime_error("Exceeded max number of components for bitmask.");
				}
				Signature next = 1ULL << nextSignature++;
				registry[type] = next;
				return next;
			}
			return 0;
		}

		template<typename T>
		Signature getComponentSignature() const
		{
			type_index type = typeid(T);
			auto it = registry.find(type);
			if (it == registry.end())
			{
				throw std::runtime_error("Component type not registered.");
			}
			return it->second;
		}

	private:
		unordered_map<type_index, Signature> registry;
		Signature nextSignature;
	};
}