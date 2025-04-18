#pragma once
#include <vector>
#include <unordered_map>
#include "icomponentarray.h"

template <typename T>
class ComponentArray : public IComponentArray {
public:
    // Add a component for an entity
    void addComponent(int entityID, const T& component) {
        if (entityToIndex.find(entityID) != entityToIndex.end())
            return; // Already has component, no need to add

        size_t index = components.size();
        entityToIndex[entityID] = index;  // Map entity to its index
        indexToEntity[index] = entityID;  // Map index to the entity
        components.push_back(component);
    }

    // Get a component for an entity
    T* getComponent(int entityID) {
        auto it = entityToIndex.find(entityID);
        if (it != entityToIndex.end()) {
            return &components[it->second];
        }
        return nullptr;
    }

    // Remove a component for an entity
    void removeComponent(int entityID) {
        auto it = entityToIndex.find(entityID);
        if (it == entityToIndex.end())
            return;

        size_t indexToRemove = it->second;
        size_t lastIndex = components.size() - 1;

        if (indexToRemove != lastIndex) {
            // Move last component to the slot of the removed one
            components[indexToRemove] = std::move(components[lastIndex]);

            // Get the entity owning the last component
            int lastEntity = indexToEntity[lastIndex];

            // Update the entity's index in both maps
            entityToIndex[lastEntity] = indexToRemove;
            indexToEntity[indexToRemove] = lastEntity;
        }

        // Pop the last component and remove the mapping
        components.pop_back();
        entityToIndex.erase(it);
        indexToEntity.erase(lastIndex);
    }

    // Check if an entity has this component
    bool hasComponent(int entityID) {
        return entityToIndex.find(entityID) != entityToIndex.end();
    }

private:
    std::vector<T> components;
    std::unordered_map<int, size_t> entityToIndex;  // Maps entity to component index
    std::unordered_map<size_t, int> indexToEntity;  // Maps component index to entity
};
