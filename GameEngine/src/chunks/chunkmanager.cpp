#include "chunkmanager.h"
#include "rendering/renderer.h"
#include "log/logger.h"
#include "glm/glm.hpp"
#include "input/input.h"

#include <string>
#include <cmath>

using std::to_string;

namespace GameEngine
{
	ChunkManager::ChunkManager()
	{
		for (auto& it : serializer.getCoordinates())
		{
			chunks.insert({ it, serializer.loadChunk(it) });
		}
	}

	ChunkManager::~ChunkManager()
	{
		for (auto& it : chunks)
		{
			serializer.unloadChunk(it.second);
			delete it.second;
		}
	}

	bool ChunkManager::addBlock(Coordinate position)
	{
		getChunkAt(position)->addBlock(position);
		dirtyChunks.insert(worldPosToChunkPos(position));
		return false;
	}

	bool ChunkManager::removeBlock(Coordinate position)
	{
		getChunkAt(position)->removeBlock(position);
		dirtyChunks.insert(worldPosToChunkPos(position));
		return false;
	}

	bool ChunkManager::isBlockAt(Coordinate position)
	{
		return getChunkAt(position)->isBlockAt(position);
		return false;
	}

	vector<AABB> ChunkManager::getColliders()
	{
		if (!dirtyChunks.empty()) {
			updateDirtyColliders();
		}
		if (collidersDirty)
		{
			cleanColliders.clear();
			for (auto& a : colliders)
			{
				cleanColliders.insert(cleanColliders.end(), a.second.begin(), a.second.end());
			}
			collidersDirty = false;
		}
		return cleanColliders;
	}

	ChunkCoordinate ChunkManager::worldPosToChunkPos(Coordinate worldPos)
	{
		return {
			(i32)(std::floor(worldPos.x / CHUNK_WIDTH_PIXELS)),
			(i32)(std::floor(worldPos.y / CHUNK_HEIGHT_PIXELS))
		};
	}

	void ChunkManager::updateDirtyColliders()
	{
		for (const auto& chunkCoord : dirtyChunks)
		{
			auto it = chunks.find(chunkCoord);
			if (it != chunks.end() && it->second)
			{
				colliders[chunkCoord] = it->second->getColliders();
				collidersDirty = true;
			}
		}
		dirtyChunks.clear();
	}

	vector<AABB>& ChunkManager::getColliderAt(Coordinate position)
	{
		return colliders[worldPosToChunkPos(position)];
	}

	Chunk* ChunkManager::getChunkAt(Coordinate position)
	{
		ChunkCoordinate key = worldPosToChunkPos(position);
		auto it = chunks.find(key);
		if (it != chunks.end()) {
			return it->second;
		}
		return nullptr;


	}

	void ChunkManager::loadChunk(Coordinate position)
	{
		ChunkCoordinate cord = worldPosToChunkPos(position);
		Chunk* c = serializer.loadChunk(cord);

		chunks.insert({ cord, c });
	}

	void ChunkManager::unloadChunk(Coordinate position)
	{
		serializer.unloadChunk(getChunkAt(position));
	}
}
