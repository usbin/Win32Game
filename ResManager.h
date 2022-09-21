#pragma once
#include "global.h"

class Texture;

class ResManager
{
	//��ü �ؽ��� map<Ű, Texture*>�� ����
	//�ؽ��� �ε� ��û������ (�̹� �ε�������� �ε� ���� �ϰ�) ����
	//�Ҹ��ڿ��� �ؽ��� ��� �Ҹ�
	SINGLETON(ResManager);
private:
	std::map<tstring, Texture*> textures_;

public:
	Texture* LoadTexture(const tstring& key, const tstring& relative_path);
};

