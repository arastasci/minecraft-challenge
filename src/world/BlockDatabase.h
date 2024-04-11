#pragma once

#include "BlockData.h"
#include <vector>
#include "BlockTypes.h"

class BlockDatabase
{
public:
	BlockDatabase();
	~BlockDatabase() = default;
	std::vector<BlockData*> blockDatabase;

};

