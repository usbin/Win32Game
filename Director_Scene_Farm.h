#pragma once
#include "global.h"
#include "RealObject.h"
class Director_Scene_Farm : public RealObject
{
public:
	Director_Scene_Farm();
	~Director_Scene_Farm();

	// RealObject��(��) ���� ��ӵ�
	virtual void Update() override;
};

