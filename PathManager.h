#pragma once
#include "global.h"
class Core;
class PathManager
{
	SINGLETON(PathManager);
private:
	tstring content_path_;
public:
	void Init();						//content_path_ 초기화
	const tstring& GetContentPath();	//content 폴더의 경로를 반환


	friend class Core;
};

