#include "chunkData.hpp"

ChunkData::ChunkData() {
    m_data = new Block[CHUNK_ARRAY_LENGTH];
}
