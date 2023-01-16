#include "TileObjectRenderComponent.h"
#include "ITileObjectInfo.h"
#include "TileObjectSprite.h"
#include "TileObject.h"

void TileObjectRenderComponent::Update(GObject* owner)
{

}

void TileObjectRenderComponent::Render(GObject* owner, ID3D11Device* p_d3d_device)
{
	if (owner) {
		TileObject* _owner = dynamic_cast<TileObject*>(owner);
		assert(_owner);
		if (_owner) {
			_owner->get_tile_object_info()->Render(_owner, p_d3d_device);
		}
	}
}

ISprite* TileObjectRenderComponent::get_sprite()
{
	return nullptr;
}

