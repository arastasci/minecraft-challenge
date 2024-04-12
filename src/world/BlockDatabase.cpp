#include "BlockDatabase.h"
BlockDatabase::BlockDatabase()
{

	blockDatabase = std::vector<BlockData*>((int)BlockId::NUM_TYPES);
	blockDatabase[(int)BlockId::Air] = new  BlockData(BlockId::Air, {0,0}, {0,0}, {0,0});
	blockDatabase[(int)BlockId::Grass] = new BlockData(BlockId::Grass, {0, 0}, {2, 0}, {3, 0});
	blockDatabase[(int)BlockId::Dirt] = new BlockData(BlockId::Dirt, {2, 0}, {2, 0}, {2, 0});
	blockDatabase[(int)BlockId::Stone] = new BlockData(BlockId::Stone, {1, 0},{1, 0},{1, 0});
}