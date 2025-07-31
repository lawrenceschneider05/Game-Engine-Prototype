#include "chunk.h"

#include <algorithm>
#include <iostream>

using std::remove;
using std::cout;

namespace GameEngine
{
    Chunk::Chunk(Coordinate _worldPosition, ChunkCoordinate _chunkPosition) : 
        worldPosition(_worldPosition), chunkPosition(_chunkPosition)
    {

    }
    void Chunk::generateColliders()
    {
        for (u32 i = 0; i < tileData.size(); i++)
        {
            const TileType& t = tileData[i];
            switch (t)
            {
            case TILE_EMPTY:
                continue;
            case TILE_GRASS:
                colliders.push_back(tileToAABB(i));
            }
        }
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
        //tileData.push_back({ chunkPos, TILE_GRASS });
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
        removeCollider(chunkPos);
    }

    bool Chunk::isBlockAt(Coordinate pos)
    {
        u32 chunkPos = worldPosToChunkPos(pos);
        return (tileData[chunkPos] == TILE_GRASS);
    }

    u32 Chunk::worldPosToChunkPos(Coordinate pos)
    {
        // Convert from world position to local tile coordinates
        f32 localX = (pos.x - worldPosition.x) / TILE_WIDTH;
        f32 localY = (pos.y - worldPosition.y) / TILE_HEIGHT;

        if (localX < 0 || localX >= CHUNK_WIDTH_TILES || localY < 0 || localY >= CHUNK_HEIGHT_TILES)
        {
            return std::numeric_limits<u32>::max(); // or any invalid value
        }

        return (u32)(localY)*CHUNK_WIDTH_TILES + (u32)(localX);
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

    vector<AABB>& Chunk::getColliders()
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

    array<TileType, CHUNK_WIDTH_TILES* CHUNK_HEIGHT_TILES>& Chunk::getTileData()
    {
        return tileData;
    }

    TileType Chunk::getTileAt(Coordinate position)
    {
        u32 pos = worldPosToChunkPos(position);
        if (pos < 256)
        {
            return tileData[pos];
        }
        return TILE_EMPTY;
    }
}