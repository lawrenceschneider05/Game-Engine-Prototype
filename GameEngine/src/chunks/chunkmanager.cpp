#include "chunkmanager.h"
#include "rendering/renderer.h"
#include "log/logger.h"
#include "glm/glm.hpp"
#include "input/input.h"

#include <string>
#include <cmath>
#include <iostream>

using std::to_string;
using std::cout;

namespace GameEngine
{
	void ChunkManager::addChunk(Chunk* c)
	{
		if (chunks.find(c->getChunkCoordinates()) != chunks.end())
		{
			delete chunks[c->getChunkCoordinates()];
		}
		chunks[c->getChunkCoordinates()] = {c};
		colliders.insert({ c->getChunkCoordinates(), c->getColliders()});
		dirtyChunks.insert(c->getChunkCoordinates());
		collidersDirty = true;
	}


	void ChunkManager::newChunk(ChunkCoordinate coord, bool filled)
	{
		Chunk* c = new Chunk(chunkPosToWorldPos(coord), coord);
		if (filled)
		{
			for (auto i = 0; i < c->getTileData().size(); i++)
			{
				c->setBlock(i);
			}
		}
		
		addChunk(c);
	}
	ChunkManager::ChunkManager()
	{
		for (auto& it : serializer.getCoordinates())
		{
			addChunk(serializer.loadChunk(it));
			
		}

		/*newChunk({0,0}, false);
		newChunk({ 1,0 }, false);
		newChunk({ -2,0 }, false);
		newChunk({ -1,0 }, false);
		newChunk({ -2,0 }, true);
		newChunk({ -3,0 }, true);*/

		/*newChunk({0,-1}, true);
		newChunk({ 1,-1 }, true);
		newChunk({ -2,-1 }, true);
		newChunk({ -1,-1 }, true);
		newChunk({ -2,-1 }, true);
		newChunk({ -3,-1 }, true);*/



	}

	ChunkManager::~ChunkManager()
	{
		for (auto& it : chunks)
		{
			serializer.unloadChunk(it.second);
			delete it.second;
		}
	}

	void ChunkManager::renderTile(TileType t, Coordinate c)
	{
		if (!t) { return; }
		switch (t)
		{
		case TILE_EMPTY:
			return;
		case TILE_GRASS:
			Renderer::drawQuad({ c.x, c.y }, { TILE_WIDTH, TILE_HEIGHT }, { 0.0f, 0.0f, 0.0f, 1.0f });
			return;
		}
	}

	void ChunkManager::renderChunk(Chunk* c)
	{
		if (!c) { return; }
		f32 chunkX = c->getWorldCoordinates().x;
		f32 chunkY = c->getWorldCoordinates().y;
		for (int i = 0; i < 256; i++)
		{
			i32 tileX = (i % 16);
			i32 tileY = (i / 16);
			f32 x = (chunkX)+tileX * TILE_WIDTH;
			f32 y = (chunkY)+tileY * TILE_HEIGHT;
			
			renderTile(c->getTileAt({ x,y }), { x, y });
		}
	}

	void ChunkManager::render()
	{
		//cout << cleanColliders.size() << "\n";
		for (auto& it : chunks)
		{
			renderChunk(it.second);
		}
	}

	bool ChunkManager::addBlock(Coordinate position)
	{
		Chunk* c = getChunkAt(position);
		if (!c)
		{
			return false;
		}
		c->addBlock(position);
		dirtyChunks.insert(worldPosToChunkPos(position));
		return false;
	}

	bool ChunkManager::removeBlock(Coordinate position)
	{
		Chunk* c = getChunkAt(position);
		if (!c)
		{
			return false;
		}
		c->removeBlock(position);
		dirtyChunks.insert(worldPosToChunkPos(position));
		return false;
	}

	bool ChunkManager::isBlockAt(Coordinate position)
	{
		Chunk* c = getChunkAt(position);
		if (!c)
		{
			return false;
		}
		return c->isBlockAt(position);
	}

	void ChunkManager::updateDirtyColliders()
	{
		for (const auto& chunkCoord : dirtyChunks)
		{
			auto it = chunks.find(chunkCoord);
			
			if (it != chunks.end() && it->second)
			{
				auto coll = it->second->getColliders();

				colliders[chunkCoord] = it->second->getColliders();
				collidersDirty = true;
			}
			else
			{
				colliders.erase(chunkCoord);
			}
		}
		dirtyChunks.clear();
	}

	const vector<AABB>& ChunkManager::getColliders()
	{
		
		updateDirtyColliders();
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

	Coordinate ChunkManager::chunkPosToWorldPos(ChunkCoordinate coordinate)
	{
		return {
		coordinate.x * CHUNK_WIDTH_PIXELS,
		coordinate.y * CHUNK_HEIGHT_PIXELS
		};
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
		//Chunk* c = serializer.loadChunk(cord);

		//chunks.insert({ cord, c });
	}

	void ChunkManager::unloadChunk(Coordinate position)
	{
		//serializer.unloadChunk(getChunkAt(position));
	}
}
