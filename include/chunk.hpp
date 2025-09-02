#pragma once
#include "constants.hpp"
#include "chunkData.hpp"
#include "mesh.hpp"

class Chunk {
    ChunkData m_chunkData;
    Mesh* m_mesh;
    glm::vec3 m_position;

public:
    Chunk(uint sizeX, uint sizeY, uint sizeZ, glm::vec3 position) : m_chunkData(sizeX, sizeY, sizeZ), m_mesh(nullptr), m_position(position) {} 

    inline Mesh* getMesh() {
        return m_mesh;
    }

    void generate();
    void updateMesh();
};
