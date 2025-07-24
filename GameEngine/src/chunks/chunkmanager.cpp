#include "chunkmanager.h"
#include "rendering/renderer.h"
#include "log/logger.h"
#include <string>

using std::to_string;

namespace GameEngine
{
	ChunkManager::ChunkManager()
	{
		/*addChunk({ -2, -1 });
		addChunk({ -1, -1 });
		addChunk({ 0, -1 });
		addChunk({ 1, -1 });
		addChunk({ 2, -1 });*/
		loadChunks();
	}
	ChunkManager::~ChunkManager()
	{
		
		for (Chunk* c : chunks)
		{
			delete c;
		}
	}
	void ChunkManager::render()
	{
		for (Chunk* c : chunks)
		{
			renderChunk(c);
		}
	}
	void ChunkManager::renderTile(TileType t, f32 x, f32 y)
	{
		switch (t)
		{
		case TILE_EMPTY:
			return;
		case TILE_GRASS:
			Renderer::drawQuad({ x, y }, { TILE_WIDTH, TILE_HEIGHT }, { 0.0f, 1.0f, 0.0f, 1.0f });
			return;
		}
	}
	void ChunkManager::renderChunk(Chunk* c)
	{
		for (int i = 0; i < 256; i++)
		{
			i32 tileX = (i % 16);
			i32 tileY = (i / 16);
			f32 x = (c->getCoordinates().x * CHUNK_WIDTH_PIXELS) + tileX * TILE_WIDTH;
			f32 y = (c->getCoordinates().y * CHUNK_HEIGHT_PIXELS) + tileY * TILE_HEIGHT;
			renderTile(c->getTile(tileX, tileY), x, y);
		}
	}
	void ChunkManager::addTile(Chunk* c, TileType t, i32 x, i32 y)
	{
		tilesUpdated = true;
		c->setTile(x, y, TILE_GRASS);
	}


	// FIX
	vector<AABB> ChunkManager::getColliders()
	{
		vector<AABB> colliders = {};
		for (Chunk* c : chunks)
		{
			for (int i = 0; i < c->getTiles().size(); i++)
			{
				i32 x = i % 16;
				i32 y = i / 16;
				if (c->getTile(x, y) == TILE_EMPTY)
				{
					continue;
				}
				AABB collider;
				collider.x = (c->getCoordinates().x * CHUNK_WIDTH_PIXELS) + x * TILE_WIDTH;
				collider.y = (c->getCoordinates().y * CHUNK_HEIGHT_PIXELS) + y * TILE_HEIGHT;
				collider.w = TILE_WIDTH;
				collider.h = TILE_HEIGHT;
				colliders.push_back(collider);
			}
		}
		return colliders;
	}

	void ChunkManager::loadChunks()
	{
		for (const ChunkCoordinate& c : serializer.getCoordinates())
		{
			Chunk* chunk = serializer.loadChunk(c);
			if (!chunk) { continue; }
			chunks.push_back(chunk);
		}
	}
}