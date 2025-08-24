#include "chunkData.hpp"

ChunkData::ChunkData(uint sizeX, uint sizeY, uint sizeZ) {
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    m_sizeZ = sizeZ;
    m_data = new Block[getLength()];
}
