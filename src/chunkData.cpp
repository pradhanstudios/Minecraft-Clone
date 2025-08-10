#include "chunkData.hpp"

ChunkData::ChunkData(uint blocksX, uint blocksY, uint blocksZ) {
    m_blocksX = blocksX;
    m_blocksY = blocksY;
    m_blocksZ = blocksZ;
    m_data = new Block[getLength()];
}
