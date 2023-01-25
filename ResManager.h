#pragma once
#include "global.h"

class Texture;
class Sound;
class ResManager
{
	//��ü �ؽ��� map<Ű, Texture*>�� ����
	//�ؽ��� �ε� ��û������ (�̹� �ε�������� �ε� ���� �ϰ�) ����
	//�Ҹ��ڿ��� �ؽ��� ��� �Ҹ�
	SINGLETON(ResManager);
private:
	std::map<tstring, Texture*> textures_;
	std::map<tstring, Sound*> sounds_;

public:
	Texture* LoadTexture(const tstring& key, const tstring& relative_path);
	Sound* LoadSound(const tstring& key, const tstring& relative_path);
	
};

