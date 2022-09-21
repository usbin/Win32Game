#pragma once
#include "global.h"

class Texture;

class ResManager
{
	//전체 텍스쳐 map<키, Texture*>로 관리
	//텍스쳐 로드 요청받으면 (이미 로드돼있으면 로드 먼저 하고) 리턴
	//소멸자에서 텍스쳐 모두 소멸
	SINGLETON(ResManager);
private:
	std::map<tstring, Texture*> textures_;

public:
	Texture* LoadTexture(const tstring& key, const tstring& relative_path);
};

