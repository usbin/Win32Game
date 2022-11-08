#pragma once
#include "global.h"
class ISavable
{
public:
	ISavable();
	~ISavable();
	virtual void SaveToFile(FILE* p_file) = 0;
	virtual void LoadFromFile(FILE* p_file) = 0;
};

