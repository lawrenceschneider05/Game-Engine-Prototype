#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <typeindex>

#include "ievent.h"

using std::function;
using std::unordered_map;
using std::vector;
using std::type_index;

using Callback = function<void(const void*)>;

namespace GameEngine
{
	class EventBus
	{
	public:

		template<typename EventType>
		void subscribe(Callback handler)
		{
			auto& handlers = subscribers[typeid(IEvent)];

			handlers.push_back([handler](const auto& e) {
				handler(static_cast<const IEvent&>(e));
				});
		}

		template<typename EventType>
		void emit(const EventType& event)
		{
			auto it = subscribers.find(typeid(EventType));
			for (it != subscribers.end())
			{
				const void* evntPtr = &event;
				for (auto& callback : it->second)
				{
					cb(eventPtr);
				}
			}
		}

	private:
		unordered_map<type_index, vector<Callback>> subscribers;
	};
}