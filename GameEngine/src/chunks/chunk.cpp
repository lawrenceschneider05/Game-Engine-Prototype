//#include "chunk.h"
//using std::fill;
//
//namespace GameEngine
//{
//	Chunk::Chunk(ChunkCoordinate coords) : coordinates(coords)
//	{
//		fill(tiles.begin(), tiles.end(), TileType::TILE_EMPTY);
//	}
//	TileType Chunk::getTile(i32 x, i32 y)
//	{
//		return tiles[indexOf(x, y)];
//	}
//
//	void Chunk::setTile(i32 x, i32 y, TileType t)
//	{
//		tiles[indexOf(x, y)] = t;
//	}
//}

#include "chunk.h"

#include <algorithm>

using std::remove;

namespace GameEngine
{
    Chunk::Chunk(Coordinate _worldPosition, ChunkCoordinate _chunkPosition) : 
        worldPosition(_worldPosition), chunkPosition(_chunkPosition)
    {

    }
	void Chunk::addBlock(Coordinate pos)
	{
        u32 chunkPos = worldPosToChunkPos(pos);
        if (tileData[chunkPos] == TILE_GRASS)
        {
            return;
        }
        dirty = true;
        addCollider(pos);
        tileData[chunkPos] = TILE_GRASS;
	}

    void Chunk::removeBlock(Coordinate pos)
    {
        u32 chunkPos = worldPosToChunkPos(pos);
        if (tileData[chunkPos] == TILE_EMPTY)
        {
            return;
        }
        dirty = true;
        tileData[chunkPos] = TILE_EMPTY;
    }

    bool Chunk::isBlockAt(Coordinate pos)
    {
        u32 chunkPos = worldPosToChunkPos(pos);
        return (chunkPos == TILE_GRASS);
    }

    u32 Chunk::worldPosToChunkPos(Coordinate pos)
    {
        f32 localX = pos.x - worldPosition.x;
        f32 localY = pos.y - worldPosition.y;

        if (localX < 0 || localX >= CHUNK_WIDTH_TILES || localY < 0 || localY >= CHUNK_HEIGHT_TILES)
        {
            return -1;
        }

        return (u32)(localY * CHUNK_WIDTH_TILES + localX);
    }

    Coordinate Chunk::chunkPosToWorldPos(u32 chunkPos)
    {
        Coordinate c;
        c.x = worldPosition.x + (chunkPos % CHUNK_WIDTH_TILES) * TILE_WIDTH;
        c.y = worldPosition.y + (chunkPos / CHUNK_HEIGHT_TILES) * TILE_HEIGHT;
        return c;
    }

    bool Chunk::isDirty()
    {
        bool b = dirty;
        dirty = false;
        return b;
    }

    vector<AABB> Chunk::getColliders()
    {
        return colliders;
    }

    AABB Chunk::tileToAABB(u32 tile)
    {
        AABB a;
        Coordinate c = chunkPosToWorldPos(tile);

        a.x = c.x;
        a.y = c.y;
        a.w = TILE_WIDTH;
        a.h = TILE_HEIGHT;

        return a;
    }

    void Chunk::addCollider(u32 tile)
    {
        colliders.push_back(tileToAABB(tile));
    }

    void Chunk::addCollider(Coordinate worldPos)
    {
        addCollider(worldPosToChunkPos(worldPos));
    }

    void Chunk::removeCollider(u32 tile)
    {
        colliders.erase(remove(colliders.begin(), colliders.end(), tileToAABB(tile)), colliders.end());
    }

    void Chunk::removeCollider(Coordinate worldPos)
    {
        removeCollider(worldPosToChunkPos(worldPos));
    }
}