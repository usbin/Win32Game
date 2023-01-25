#include "FarmhouseDoor.h"
#include "Interactor.h"
#include "FmodSound.h"
#include "ResManager.h"
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
	//다음 맵으로 이동
	ChangeScene(SCENE_TYPE::SCENE_FARMHOUSE);
	Sound* sound = ResManager::GetInstance()->LoadSound(_T("DoorOpen_Effect"), _T("sound\\DoorOpen_Effect.wav"));
	FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), sound, false);
}
