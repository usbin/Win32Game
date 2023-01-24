#pragma once
#include "global.h"
#include "FileSaver1_0_0.h"
class Topground;
class FileSaver1_1_0 : public FileSaver1_0_0
{
public:
	void SaveTopground(FILE* p_file, Topground* topground);
	Topground* LoadTopground(FILE* p_file);
	virtual void SaveMapToFile(FILE* p_file) override;
	virtual void LoadMapFromFile(FILE* p_file) override;
};

