#include "Scene_01.h"
#include "KeyManager.h"
#include "Time.h"
#include "Player.h"
#include "CollisionManager.h"
#include "TimerUi.h"
#include "ResManager.h"
#include "Sprite.h"
bool Scene_01::Enter()
{
	GObject* gobj = new Player();
	gobj->set_pos(Vector2{ 500, 500 });
	gobj->set_scale(Vector2{ 50, 50 });
	gobj->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(gobj, GROUP_TYPE::PLAYER);

	TimerUi* timer_ui = new TimerUi();
	timer_ui->set_pos(Vector2(0, 0));
	timer_ui->set_scale(Vector2(200, 100));
	timer_ui->set_group_type(GROUP_TYPE::UI);
	CreateGObject(timer_ui, GROUP_TYPE::UI);
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Ingame Timer Ui Background"), _T("texture\\black.png"));
	Sprite* sprite = new Sprite();
	sprite->QuickSet(texture, timer_ui, timer_ui->get_pos(), timer_ui->get_scale());
	timer_ui->ChangeSprite(sprite);
	

		
	return TRUE;
}


bool Scene_01::Exit()
{
	Scene::DeleteAllObjects();
	return TRUE;
}
