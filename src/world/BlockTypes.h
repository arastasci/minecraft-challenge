#pragma once
#include <cstdint>

enum class BlockId : uint8_t {
    Air = 0,
    Grass = 1,
    Dirt = 2,
    Stone = 3,
    OakBark = 4,
    OakLeaf = 5,
    Sand = 6,
    Water = 7,
    Cactus = 8,
    Rose = 9,
    TallGrass = 10,
    DeadShrub = 11,

    NUM_TYPES
};