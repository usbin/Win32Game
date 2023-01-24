#pragma once
#include "global.h"
#include "IFileSaver.h"

class Core;

//1. 맵 저장, 불러오기
class FileManager
{
	SINGLETON(FileManager);
	
private:
	IFileSaver* file_saver_ = nullptr;
	IFileSaver* old_saver_ = nullptr;
public:
	void SaveMap(const tstring& file_path); //현재 씬의 BACKGROUND, TILE, INVISIBLE_WALL을 .map 파일로 저장. (Tool씬에서만 동작)
	void LoadMap(const tstring& file_path);

	void SaveWallFile(const tstring& file_path);	// INVISIBLE_WALL을 저장하고 불러오기
	void LoadWallFile(const tstring& file_path);

	void SaveTilemapFile(const tstring& file_path);
	void LoadTilemapFile(const tstring& file_path);


	friend class Core;
};

