#include "tilemanager.h"
#include "rendering/renderer.h"
#include "log/logger.h"
#include <string>

using std::to_string;

namespace GameEngine
{
	TileManager::TileManager()
	{
		addChunk((-CHUNK_WIDTH_PIXELS / 2), (-CHUNK_HEIGHT_PIXELS / 2));
		addChunk((CHUNK_WIDTH_PIXELS / 2), (-CHUNK_HEIGHT_PIXELS / 2));
		addChunk((-3 * CHUNK_WIDTH_PIXELS / 2), (-CHUNK_HEIGHT_PIXELS / 2));
	}
	TileManager::~TileManager()
	{
		for (Chunk* c : chunks)
		{
			delete c;
		}
	}
	void TileManager::render()
	{
		for (Chunk* c : chunks)
		{
			renderChunk(c);
		}
	}
	void TileManager::renderTile(TileType t, f32 x, f32 y)
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
	void TileManager::renderChunk(Chunk* c)
	{
		for (int y = 0; y < CHUNK_HEIGHT_TILES; y++)
		{
			for (int x = 0; x < CHUNK_WIDTH_TILES; x++)
			{
				renderTile(c->getTile(x, y), c->getX() + ((float)x * TILE_WIDTH), c->getY() + ((float)y * TILE_HEIGHT));
			}
		}
		Renderer::drawQuad({ c->getX(), c->getY() }, { CHUNK_WIDTH_PIXELS, CHUNK_HEIGHT_PIXELS }, { 0.0f, 0.0f, 0.0f, 1.0f });
	}
	void TileManager::addTile(Chunk* c, TileType t, f32 x, f32 y)
	{
		tilesUpdated = true;
		c->setTile(x, y, TILE_GRASS);
	}
}