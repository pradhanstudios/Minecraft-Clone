#pragma once
#include "constants.hpp"
#include "chunk.hpp"

class World {
    Chunk* m_chunks;
    uint m_renderDistance;
    uint m_chunkSizeX;
    uint m_chunkSizeY;
    uint m_chunkSizeZ;

    inline Chunk* getChunkArrayCoordinates(uint x, uint z) {
        return m_chunks[x*m_renderDistance + z];
    }
public:
    World(uint renderDistance, uint chunkSizeX, uint chunkSizeY, uint chunkSizeZ);

    inline Chunk* getChunkAtCoordinates(glm::vec3 coordinates, glm::vec3 playerPosition) {
        coordinates -= playerPosition;
        int x = coordinates.x / m_chunkSizeX;
        x += m_chunkSizeX / 2; 
        int z = coordinates.z / m_chunkSizeZ;
        z += m_chunkSizeZ / 2;

        return getChunkArrayCoordinates((uint)x, (uint)z);
    }

    inline 
    // void changeRenderDistance(uint renderDistance);
}
