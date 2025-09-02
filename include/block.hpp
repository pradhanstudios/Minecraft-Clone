#pragma once
#include "constants.hpp"

enum {
    BLOCK_AIR,
    BLOCK_DIRT,



    NUMBER_OF_BLOCKS
};

class Block {
public:
    bool transparent;

    inline bool isTransparent() {
        return transparent;
    }
};

inline Block blockArray[NUMBER_OF_BLOCKS] = {};

// Hacking c++ to let me assign global variables :(
namespace {
    struct _BlockInitializer {
        _BlockInitializer() {
            blockArray[BLOCK_AIR] = {true};
            blockArray[BLOCK_DIRT] = {false};
        }
    };

    inline _BlockInitializer _block_initializer_instance;
}
