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
    m_generated = true;
    for (uint i = 0; i < CHUNK_ARRAY_LENGTH; i++) {
        m_chunkData.setBlock(i, blockArray[BLOCK_DIRT]);
    }
}

void Chunk::updateMesh() {
    std::vector<float> vertices;

    std::reference_wrapper<const float[18]> blockFaces[] = {
        std::ref(cubeVerticesFront),
        std::ref(cubeVerticesBack),
        std::ref(cubeVerticesLeft),
        std::ref(cubeVerticesRight),
        std::ref(cubeVerticesTop),
        std::ref(cubeVerticesBottom)
    };

    size_t faceSize = sizeof(cubeVerticesFront) / sizeof(float);
    for (uint x = 0; x < CHUNK_SIZE_X; x++)
    for (uint y = 0; y < CHUNK_SIZE_Y; y++)
    for (uint z = 0; z < CHUNK_SIZE_Z; z++) {
        Block currBlock = m_chunkData.getBlock(x, y, z);
        if (currBlock.isTransparent()) {
            continue;
        }

        glm::vec3 worldPos = glm::vec3(float(x), float(y), float(z)) + m_position;
        for (int i = 0; i < 6; i++) {
            if ((i == 0 && z == (CHUNK_SIZE_Z - 1)) || (i == 1 && z == 0) || (i == 2 && x == 0) || (i == 3 && x == (CHUNK_SIZE_X-1)) || (i == 4 && y == (CHUNK_SIZE_Y-1)) || (i == 5 && y == 0) || m_chunkData.getBlock(
                glm::clamp(x+blockOffsets[i], 0u, CHUNK_SIZE_X-1u),
                glm::clamp(y+blockOffsets[i*2], 0u, CHUNK_SIZE_Y-1u),
                glm::clamp(z+blockOffsets[i*3], 0u, CHUNK_SIZE_Z-1u)
            ).isTransparent()) {
                addFace(vertices, (blockFaces[i]), faceSize, worldPos);
            }
        }
        // if (z != (CHUNK_SIZE_Z-1) && m_chunkData.getBlock(x, y, z+1).isTransparent())
        //     addFace(vertices, cubeVerticesFront, faceSize, worldPos);
        // if (z != 0 && m_chunkData.getBlock(x, y, z-1).isTransparent())
        //     addFace(vertices, cubeVerticesBack, faceSize, worldPos);
        // if (x != 0 && m_chunkData.getBlock(x-1, y, z).isTransparent())
        //     addFace(vertices, cubeVerticesLeft, faceSize, worldPos);
        // if (x != (CHUNK_SIZE_X-1) && m_chunkData.getBlock(x+1, y, z).isTransparent())
        //     addFace(vertices, cubeVerticesRight, faceSize, worldPos);
        // if (y != (CHUNK_SIZE_Y-1) && m_chunkData.getBlock(x, y+1, z).isTransparent())
        //     addFace(vertices, cubeVerticesTop, faceSize, worldPos);
        // if (y != 0 && m_chunkData.getBlock(x, y-1, z).isTransparent())
        //     addFace(vertices, cubeVerticesBottom, faceSize, worldPos);
    }

    if (m_mesh) {
        m_mesh->bind();
        glBindBuffer(GL_ARRAY_BUFFER, m_mesh->getVBOID());
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        m_mesh->unbind();
    }

    else {
        m_mesh = new Mesh(vertices.data(), vertices.size());
    }
}
