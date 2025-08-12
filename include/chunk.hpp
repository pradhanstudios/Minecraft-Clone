#pragma once
#include "constants.hpp"
#include "chunkData.hpp"

class Chunk {
    ChunkData m_chunkData;
    glm::vec3 m_position;

public:
    Chunk(uint blocksX, uint blocksY, uint blocksZ, glm::vec3 position) : m_chunkData(blocksX, blocksY, blocksZ), m_position(position) {} 

    void generate();
};
