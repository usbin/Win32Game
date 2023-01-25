#include "TileObject.h"
#include "TileObjectRenderComponent.h"
#include "ITileObjectInfo.h"
#include "TileObjectDb.h"
#include "Collider.h"
TileObject::~TileObject()
{
		
}
void TileObject::Init(TILE_OBJECT_TYPE type) {
	tile_object_info_ = TileObjectDb::GetInstance()->get_tile_object_info(type);
	tile_object_type_ = type;


	CreateRenderCmp();

	switch (tile_object_type_)
	{
	case TILE_OBJECT_TYPE::STONE:
	case TILE_OBJECT_TYPE::WOOD:
	case TILE_OBJECT_TYPE::WEED:
		CreateCollider();
		break;
	case TILE_OBJECT_TYPE::FIELD:
		break;
	}
}
void TileObject::CreateCollider()
{
	Collider* collider = DEBUG_NEW Collider();
	collider->set_owner(this);
	collider->set_is_physical_collider(true);
	collider->set_scale(get_scale());
	set_collider(collider);

}
void TileObject::SetLevel(UINT level) {
	level_ = level;
}
void TileObject::Update()
{	
	updated_day_ = Game::GetInstance()->get_day();
}

void TileObject::CreateRenderCmp()
{
	render_cmp_ = new TileObjectRenderComponent();
}

void TileObject::Render(ID3D11Device* p_d3d_device)
{
	render_cmp_->Render(this, p_d3d_device);
	ComponentRender(p_d3d_device);
}

const ITileObjectInfo* TileObject::get_tile_object_info() {
	return tile_object_info_;
}
