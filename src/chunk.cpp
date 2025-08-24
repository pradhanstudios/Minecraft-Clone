#include "chunk.hpp"

void Chunk::generate() {
    for (uint i = 0; i < m_chunkData->getLength(); i++) {
        m_chunkData->setBlock(i, blockArray[BLOCK_DIRT]);
    }
}

void Chunk::updateMesh() {
    

    for (uint x = 0; x < m_chunkData->getSizeX(); x++)
    for (uint y = 0; y < m_chunkData->getSizeY(); y++)
    for (uint z = 0; z < m_chunkData->getSizeZ(); z++) {
        Block currBlock = m_chunkData->getBlock(x, y, z);
        if (currBlock.isTransparent()) {
            continue;
        }


    }
}
