#pragma once
#include "global.h"
//1. �� ����, �ҷ�����
class FileManager
{
	SINGLETON(FileManager);

public:
	void SaveMap(const tstring& file_path); //���� ���� BACKGROUND, TILE, INVISIBLE_WALL�� .map ���Ϸ� ����. (Tool�������� ����)
	void LoadMap(const tstring& file_path);
};

