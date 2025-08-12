#include "chunk.hpp"

void Chunk::generate() {
    for (uint i = 0; i < m_chunkData.getLength(); i++) {
        m_chunkData.setBlock(i, blockArray[BLOCK_DIRT]);
    }
}
