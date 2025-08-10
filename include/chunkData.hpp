#pragma once
#include "constants.hpp"
#include "block.hpp"

class ChunkData {
    Block* m_data;
    uint m_blocksX;
    uint m_blocksY;
    uint m_blocksZ;
    
    inline uint coordTo1D(uint x, uint y, uint z) const {
        assert(x < m_blocksX);
        assert(y < m_blocksY);
        assert(z < m_blocksZ);
        return x + (y * m_blocksY) + (z * m_blocksY * m_blocksZ);
    }

public:
    ChunkData(uint blocksX, uint blocksY, uint blocksZ);
    ~ChunkData() { delete[] m_data; }
    
    inline size_t getLength() const {
        return m_blocksX * m_blocksY * m_blocksZ;
    }

    inline Block getBlock(uint x, uint y, uint z) const {
        return (m_data[coordTo1D(x, y, z)]);
    }

    inline void setBlock(uint x, uint y, uint z, Block& block) {
        m_data[coordTo1D(x, y, z)] = block;
    }

    inline Block* getPointer() {
        return m_data;
    }
};
