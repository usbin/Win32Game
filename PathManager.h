#pragma once
#include "global.h"
class PathManager
{
	SINGLETON(PathManager);
private:
	tstring content_path_;
public:
	void Init();						//content_path_ �ʱ�ȭ
	const tstring& GetContentPath();	//content ������ ��θ� ��ȯ
};

