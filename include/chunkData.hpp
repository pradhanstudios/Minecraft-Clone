#pragma once
#include "constants.hpp"
#include "block.hpp"

class ChunkData {
    Block* m_data;
    uint m_sizeX;
    uint m_sizeY;
    uint m_sizeZ;
    
    inline uint coordTo1D(uint x, uint y, uint z) const {
        assert(x < m_sizeX);
        assert(y < m_sizeY);
        assert(z < m_sizeZ);
        return x + (y * m_sizeY) + (z * m_sizeY * m_sizeZ);
    }

public:
    ChunkData(uint sizeX, uint sizeY, uint sizeZ);
    ~ChunkData() { delete[] m_data; }
    
    inline size_t getLength() const {
        return m_sizeX * m_sizeY * m_sizeZ;
    }

    inline size_t getSizeX() const {
        return m_sizeX;
    }

    inline size_t getSizeY() const {
        return m_sizeY;
    }
    
    inline size_t getSizeZ() const {
        return m_sizeZ;
    }

    inline Block getBlock(uint x, uint y, uint z) const {
        return m_data[coordTo1D(x, y, z)];
    }

    inline Block getBlock(uint i) const {
        return m_data[i];
    }

    inline void setBlock(uint x, uint y, uint z, Block& block) {
        m_data[coordTo1D(x, y, z)] = block;
    }

    inline void setBlock(uint i, Block& block) {
        m_data[i] = block;
    }

    inline Block* getPointer() {
        return m_data;
    }

    inline uint getSizeX() {
        return m_sizeX;
    }
 
    inline uint getSizeY() {
        return m_sizeY;
    }

    inline uint getSizeZ() {
        return m_sizeZ;
    }
};
