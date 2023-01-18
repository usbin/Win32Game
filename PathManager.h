#pragma once
#include "global.h"
class Core;
class PathManager
{
	SINGLETON(PathManager);
private:
	tstring content_path_;
public:
	void Init();						//content_path_ �ʱ�ȭ
	const tstring& GetContentPath();	//content ������ ��θ� ��ȯ


	friend class Core;
};

