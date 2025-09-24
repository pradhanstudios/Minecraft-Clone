#include "world.hpp"

void World::createChunk(uint x, uint z, glm::vec3 offset) {
    Chunk* currChunk = getChunkArrayCoordinates(x, z);
    assert(currChunk == nullptr || !currChunk->hasBeenGenerated());
    if (currChunk == nullptr) {
        currChunk = new Chunk(localToChunkCoords(x, z) + offset);
        m_chunks[arrayCoordinates(x, z)] = currChunk;
    }

    currChunk->generate();
    currChunk->updateMesh();
}

void World::unloadChunk(uint x, uint z) {
    Chunk* chunk = getChunkArrayCoordinates(x, z);
    assert(chunk != nullptr);
    _saveChunk(chunk);
    delete chunk;
    m_chunks[arrayCoordinates(x, z)] = nullptr;
}

void World::saveChunk(Chunk* chunk) {
    ;
}

void getLocalChunkCoordinatesPlayer(uint& x, uint& z) {
    glm::vec3 topLeftChunkPosition = getChunk1D(0u)->getPosition();
    x = uint((topLeftChunkPosition - m_playerPosition.x) / 16.f)
}

void World::generateWorld() {
    glm::vec3 worldSize = {m_renderDistance * CHUNK_SIZE_X, m_renderDistance * CHUNK_SIZE_Y, m_renderDistance * CHUNK_SIZE_Z};
    std::cout << m_playerPosition.z << std::endl;
    for (uint x = 0; x < m_renderDistance; x++) {
        for (uint z = 0; z < m_renderDistance; z++) {
            createChunk(x, z, {m_playerPosition.x - (worldSize.x * 0.5f), m_playerPosition.y - CHUNK_SIZE_Y, -m_playerPosition.z + (worldSize.z * 0.5f)});
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
