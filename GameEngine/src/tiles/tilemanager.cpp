#include "tilemanager.h"
#include "rendering/renderer.h"
#include "log/logger.h"
#include <string>

using std::to_string;

namespace GameEngine
{
	TileManager::TileManager() : testingChunk(-((i32)CHUNK_WIDTH_PIXELS / 2), -((i32)CHUNK_HEIGHT_PIXELS / 2))
	{
		for (int y = 0; y < CHUNK_HEIGHT_TILES; y++)
		{
			for (int x = 0; x < CHUNK_WIDTH_TILES; x++)
			{
				testingChunk.setTile(x, y, TILE_GRASS);
			}
		}
	}
	TileManager::~TileManager()
	{
	}
	void TileManager::render()
	{
		
		for (int y = 0; y < CHUNK_HEIGHT_TILES; y++)
		{
			for (int x = 0; x < CHUNK_WIDTH_TILES; x++)
			{
				renderTile(testingChunk.getTile(x, y), testingChunk.getX() + (x * TILE_WIDTH), testingChunk.getY() + (y * TILE_HEIGHT));
			}
		}
	}
	void TileManager::renderTile(TileType t, u32 x, u32 y)
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
}