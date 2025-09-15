#pragma once
#include "constants.hpp"
#include "chunkData.hpp"
#include "mesh.hpp"

class Chunk {
    ChunkData m_chunkData;
    Mesh* m_mesh;
    glm::vec3 m_position;
    bool m_generated;

public:
    Chunk(glm::vec3 position) : m_chunkData(), m_mesh(nullptr), m_position(position), m_generated(false) {}

    inline Mesh* getMesh() const {
        return m_mesh;
    }

    inline Block getBlock(uint x, uint y, uint z) const {
        return m_chunkData->getBlock(x, y, z);
    }

    inline bool hasBeenGenerated() const {
        return m_generated;
    }

    inline glm::vec3 getPosition() const {
        return m_position;
    } 

    void generate();
    void updateMesh();
};
