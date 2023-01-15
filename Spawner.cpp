#include "Spawner.h"
#include "SceneManager.h"
#include "TileObject.h"
Spawner::Spawner() {};
Spawner::~Spawner() {};
void Spawner::RandomSpawn(TILE_OBJECT_TYPE type, Vector2 left_top, Vector2 bottom_right, UINT amount)
{
	//left ~ right ���� / TILE_WIDTH, top~bottom / TILE_HEIGHT ���̿��� ���� amount���� ���� ������ �̱�(������ �� Ÿ�Ͽ� �ϳ��� ���� �� �����Ƿ�)
	srand(time(0));
	int max_column = static_cast<int>(bottom_right.x - left_top.x)/TILE_WIDTH;
	int max_row = static_cast<int>(bottom_right.y - left_top.y) / TILE_HEIGHT;
	
	int failed = 0;
	for (int i = 0; i < amount; i++) {
		int column = rand() % max_column;
		int row = rand() % max_row;
		Vector2 pos{ column * TILE_WIDTH + (TILE_WIDTH/2), row * TILE_HEIGHT + (TILE_HEIGHT/2)};
		Vector2 out_pos{};
		TileObject* out_tile_obj = nullptr;
		SceneManager::GetInstance()->get_current_scene()->GetTileObject(pos, out_pos, out_tile_obj);
		if (out_tile_obj) {
			//20�� �Ѱ� �����ϸ� �׳� break;
			if (failed < 20) {
				failed++;
				i--;
			}
			else break;
		}
		else {
			TileObject* tile_object = new TileObject();
			tile_object->Init(type);
			tile_object->set_pos(pos + Vector2{ TILE_WIDTH, TILE_HEIGHT }/2.f);
			tile_object->set_scale(Vector2{ TILE_WIDTH, TILE_HEIGHT });
			CreateGObject(tile_object, GROUP_TYPE::TILE_OBJECT);
		}

	}

}
