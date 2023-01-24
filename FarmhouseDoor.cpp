#include "FarmhouseDoor.h"
#include "Interactor.h"
FarmhouseDoor::~FarmhouseDoor()
{
}
void FarmhouseDoor::Init()
{
	CreateInteractor();
}

void FarmhouseDoor::CreateInteractor()
{
	Interactor* interactor = DEBUG_NEW Interactor();
	interactor->Init(this, Vector2{ 0, 0 }, get_scale());
	CreateGObject(interactor, GROUP_TYPE::INTERACTOR);
	interactor_ = interactor;
}

void FarmhouseDoor::Update()
{
}

void FarmhouseDoor::OnInteract(const GObject* gobj)
{
	//���� ������ �̵�
	ChangeScene(SCENE_TYPE::SCENE_FARMHOUSE);
}
