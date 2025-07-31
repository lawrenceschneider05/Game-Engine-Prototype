#pragma once
#include "ichunkmanager.h"
#include "physics/aabb.h"
#include "chunk.h"
#include "chunkserializer.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>


using std::vector;
using std::unordered_map;
using std::unordered_set;

namespace GameEngine
{
	
	
	class ChunkManager : public IChunkManager
	{
	public:
		ChunkManager();
		~ChunkManager();

		bool addBlock(Coordinate position) override;
		bool removeBlock(Coordinate position) override;
		bool isBlockAt(Coordinate position) override;

		void render();

		void updateDirtyColliders();
		const vector<AABB>& getColliders();
	private:
		Chunk* getChunkAt(Coordinate position);
		ChunkCoordinate worldPosToChunkPos(Coordinate position);
		Coordinate chunkPosToWorldPos(ChunkCoordinate coordinate);
		vector<AABB>& getColliderAt(Coordinate position);

		void loadChunk(Coordinate position);
		void unloadChunk(Coordinate position);

		void renderTile(TileType, Coordinate c);
		void renderChunk(Chunk* c);

		
	private:
		void addChunk(Chunk* c);
		void newChunk(ChunkCoordinate coords, bool filled);
	private:
		bool collidersDirty = false;
		unordered_map<ChunkCoordinate, Chunk*> chunks{};
		unordered_map<ChunkCoordinate, vector<AABB>> colliders{};
		unordered_set<ChunkCoordinate> dirtyChunks{};
		vector<AABB> cleanColliders;

		ChunkSerializer serializer;
	};
}
