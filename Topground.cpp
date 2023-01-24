#include "Topground.h"
#include "RealObjectSprite.h"
#include "RealObjectRenderComponent.h"

Topground::Topground() {
	CreateRenderCmp();
}
void Topground::CreateRenderCmp()
{
	RealObjectRenderComponent* cmp = DEBUG_NEW RealObjectRenderComponent(this);
	cmp->set_render_layer(RENDER_LAYER::PLAYER);
	render_cmp_ = cmp;

}
void Topground::Update()
{

}

void Topground::Render(ID3D11Device* p_d3d_device)
{
	render_cmp_->Render(this, p_d3d_device);
}
