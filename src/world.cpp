#include "world.hpp"

void World::createChunk(uint x, uint z) {
    Chunk* currChunk = getChunkArrayCoordinates(x, z);
    assert(currChunk == nullptr || !currChunk->hasBeenGenerated());
    if (currChunk == nullptr) {
        currChunk = new Chunk(localToChunkCoords(x, z));
        m_chunks[arrayCoordinates(x, z)] = currChunk;
    }

    currChunk->generate();
    currChunk->updateMesh();
}

void World::unloadChunk(uint x, uint z) {
    // Chunk* currChunk = getChunkArrayCoordinates(x, z);
    // _saveChunkData(currChunk)
}

void World::_saveChunkData(Chunk* chunk) {

}

void World::generateWorld() {
    for (uint x = 0; x < m_renderDistance; x++) {
        for (uint z = 0; z < m_renderDistance; z++) {
            createChunk(x, z);
        }
    }
}

void World::render(Renderer& renderer, Shader& shader, const Camera& camera) {
    for (uint i = 0; i < (m_renderDistance * m_renderDistance); i++) {
        assert(m_chunks[i] != nullptr);
        assert(m_chunks[i]->hasBeenGenerated());
        renderer.draw(*(m_chunks[i]->getMesh()), shader, camera);
    }
}
// void World::changeRenderDistance(uint renderDistance) {
//     m_renderDistance = renderDistance;
//     m_chunks = (Chunk *)malloc(siezof(Chunk) * m_renderDistance * m_renderDistance);
// }
