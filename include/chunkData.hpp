#pragma once
#include "constants.hpp"
#include "block.hpp"

class ChunkData {
    Block* m_data;

    inline uint coordTo1D(uint x, uint y, uint z) const {
        assert(x < CHUNK_SIZE_X);
        assert(y < CHUNK_SIZE_Y);
        assert(z < CHUNK_SIZE_Z);
        return x + (y * CHUNK_SIZE_Y) + (z * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
    }

public:
    ChunkData();
    ~ChunkData() { delete[] m_data; }

    inline Block getBlock(uint x, uint y, uint z) const {
        return m_data[coordTo1D(x, y, z)];
    }

    inline Block getBlock(uint i) const {
        return m_data[i];
    }

    inline void setBlock(uint x, uint y, uint z, Block block) {
        m_data[coordTo1D(x, y, z)] = block;
    }

    inline void setBlock(uint i, Block block) {
        m_data[i] = block;
    }

    inline Block* getPointer() {
        return m_data;
    }
};
