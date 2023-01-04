#include "Background.h"
#include "Texture.h"
#include "RealObjectRenderComponent.h"

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
	render_cmp_ = DEBUG_NEW RealObjectRenderComponent(this);
}
