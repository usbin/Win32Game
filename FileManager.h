#pragma once
#include "global.h"
#include "IFileSaver.h"

class Core;

//1. �� ����, �ҷ�����
class FileManager
{
	SINGLETON(FileManager);
	
private:
	IFileSaver* file_saver_ = nullptr;
	IFileSaver* old_saver_ = nullptr;
public:
	void SaveMap(const tstring& file_path); //���� ���� BACKGROUND, TILE, INVISIBLE_WALL�� .map ���Ϸ� ����. (Tool�������� ����)
	void LoadMap(const tstring& file_path);

	void SaveWallFile(const tstring& file_path);	// INVISIBLE_WALL�� �����ϰ� �ҷ�����
	void LoadWallFile(const tstring& file_path);

	void SaveTilemapFile(const tstring& file_path);
	void LoadTilemapFile(const tstring& file_path);


	friend class Core;
};

