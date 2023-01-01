#include "Background.h"
#include "Sprite.h"
#include "Texture.h"

Background::Background()
{
	CreateRenderCmp();
}

Background::~Background()
{
}

void Background::Update()
{
}

void Background::CreateRenderCmp()
{
	render_cmp_ = new RealObjectRenderComponent(this);
}
