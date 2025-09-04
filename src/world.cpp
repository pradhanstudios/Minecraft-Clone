#include "world.hpp"

World::World(uint renderDistance, uint chunkSizeX, uint chunkSizeY, uint chunkSizeZ) {
    m_renderDistance = renderDistance;
    // Render distance should be even
    assert((m_renderDistance % 2) == 0);
    m_chunkSizeX = chunkSizeX;
    m_chunkSizeY = chunkSizeY;
    m_chunkSizeZ = chunkSizeZ;
    m_chunks = (Chunk *)malloc(siezof(Chunk) * m_renderDistance * m_renderDistance);
}


// void World::changeRenderDistance(uint renderDistance) { 
//     m_renderDistance = renderDistance;
//     m_chunks = (Chunk *)malloc(siezof(Chunk) * m_renderDistance * m_renderDistance);
// }
