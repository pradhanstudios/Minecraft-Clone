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

    inline Mesh* getMesh() {
        return m_mesh;
    }

    inline bool hasBeenGenerated() {
        return m_generated;
    }

    void generate();
    void updateMesh();
};
