#pragma once
#include "constants.hpp"
#include "chunk.hpp"
#include "renderer.hpp"

class World {
    Chunk** m_chunks;
    glm::vec3& m_playerPosition;
    uint m_renderDistance;

    inline uint arrayCoordinates(uint x, uint z) const {
        return x * m_renderDistance + z;
    }

    inline Chunk* getChunkArrayCoordinates(uint x, uint z) const {
        return m_chunks[arrayCoordinates(x, z)];
    }

    inline glm::vec3 localToChunkCoords(uint x, uint z) {
        return {x * 16.f, 0.f, z * 16.f};
    }

    void createChunk(uint x, uint z);
    void loadChunk(uint x, uint z);
    void unloadChunk(uint x, uint z);
    void _saveChunkData(Chunk* data);

public:
    World(glm::vec3 playerPosition, uint renderDistance)
        : m_renderDistance(renderDistance), m_playerPosition(playerPosition) {
        assert(m_renderDistance % 2 == 0);
        m_chunks = new Chunk*[m_renderDistance * m_renderDistance];
        for (int i = 0; i < lengthOfArray(); i++) {
            m_chunks[i] = nullptr;
        }

        std::cout << "World initialization complete" << std::endl;
    }

    ~World() {
        for (int i = 0; i < lengthOfArray(); i++) {
            delete m_chunks[i];
        }

        delete[] m_chunks;
        std::cout << "World destroyed" << std::endl;
    }

    void generateWorld();
    void render(Renderer& renderer, Shader& shader, const Camera& camera);

    inline uint lengthOfArray() {
        return m_renderDistance * m_renderDistance;
    }

    inline Chunk* getChunk1D(uint x) {
        return m_chunks[x];
    }

    inline Chunk* getChunkAtCoordinates(glm::vec3 coordinates) {
        coordinates -= m_playerPosition;
        int x = coordinates.x / CHUNK_SIZE_X;
        int z = coordinates.z / CHUNK_SIZE_Z;

        // Adjust for negative coordinates
        x += m_renderDistance / 2;
        z += m_renderDistance / 2;

        assert(0 <= x < m_renderDistance);
        assert(0 <= z < m_renderDistance);

        return getChunkArrayCoordinates((uint)x, (uint)z);
    }

    // void changeRenderDistance(uint renderDistance);
};
