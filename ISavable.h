#pragma once
#include "global.h"
class ISavable
{
public:
	virtual void SaveToFile(FILE* p_file) = 0;
	virtual void LoadFromFile(FILE* p_file) = 0;
};

