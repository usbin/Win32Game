#pragma once
#include "global.h"
#include "RealObject.h"
class Director_Scene_01 : public RealObject
{
public:
	Director_Scene_01();
	~Director_Scene_01();

	// RealObject��(��) ���� ��ӵ�
	virtual void Update() override;
};

