#include "chunk.hpp"

void addFace(std::vector<float>& vertices, const float* face, size_t face_length, glm::vec3 offset) {
    vertices.reserve(vertices.size() + face_length);
    for (int i = 0; i < face_length; i += 3) {
        vertices.push_back(face[i] + offset.x);
        vertices.push_back(face[i+1] + offset.y);
        vertices.push_back(face[i+2] + offset.z);
    }
}

void Chunk::generate() {
    for (uint i = 0; i < m_chunkData.getLength(); i++) {
        m_chunkData.setBlock(i, blockArray[BLOCK_DIRT]);
    }
}

void Chunk::updateMesh() {
    std::vector<float> vertices;

    size_t faceSize = sizeof(cubeVerticesFront) / sizeof(float);
    for (uint x = 0; x < m_chunkData.getSizeX(); x++)
    for (uint y = 0; y < m_chunkData.getSizeY(); y++)
    for (uint z = 0; z < m_chunkData.getSizeZ(); z++) {
        Block currBlock = m_chunkData.getBlock(x, y, z);
        if (currBlock.isTransparent()) {
            continue;
        }
        
        glm::vec3 offset = {float(x), float(y), float(z)};
        addFace(vertices, cubeVerticesFront, faceSize, offset);
        addFace(vertices, cubeVerticesBack, faceSize, offset);
        addFace(vertices, cubeVerticesLeft, faceSize, offset);
        addFace(vertices, cubeVerticesRight, faceSize, offset);
        addFace(vertices, cubeVerticesTop, faceSize, offset);
        addFace(vertices, cubeVerticesBottom, faceSize, offset);
    }

    if (m_mesh) {
        m_mesh->bind();
        glBindBuffer(GL_ARRAY_BUFFER, m_mesh->getVBOID());
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        m_mesh->unbind();
    }

    else {
        std::cout << "got here" << std::endl;
        m_mesh = new Mesh(vertices.data(), vertices.size());
        std::cout << "got here" << std::endl;
    }
}
