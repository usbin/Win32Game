#include "Sprite.h"
#include "GObject.h"
#include "Texture.h"

Sprite::Sprite()
	: texture_(nullptr)
	, base_pos_{}
	, scale_{}
	, owner_(nullptr)
{
}

Sprite::Sprite(const Sprite& org)
	: texture_(org.texture_)
	, base_pos_(org.base_pos_)
	, scale_(org.scale_)
	, owner_(nullptr)
{
}

Sprite::~Sprite()
{
}


void Sprite::QuickSet(Texture* texture, GObject* owner, int row, int column, int max_row, int max_column)
{
	texture_ = texture;
	owner_ = owner;
	base_pos_ = Vector2{(texture->get_width() / max_column) * static_cast<double>(column), (texture_->get_height() / max_row) * static_cast<double>(row) };
	scale_ = Vector2{ texture->get_width() / static_cast<double>(max_column), texture_->get_height() / static_cast<double>(max_row) };
}

void Sprite::QuickSet(Texture* texture, GObject* owner, Vector2 base_pos, Vector2 scale)
{
	texture_ = texture;
	owner_ = owner;
	base_pos_ = base_pos;
	scale_ = scale;
}

void Sprite::SaveToFile(FILE* p_file)
{
	texture_->SaveToFile(p_file);
	fwrite(&base_pos_, sizeof(Vector2), 1, p_file);
	fwrite(&scale_, sizeof(Vector2), 1, p_file);
	
}

void Sprite::LoadFromFile(FILE* p_file)
{
	Res* res = new Res();
	res->LoadFromFile(p_file);
	texture_ = ResManager::GetInstance()->LoadTexture(res->get_key(), res->get_relative_path());
	delete res;
	fread(&base_pos_, sizeof(Vector2), 1, p_file);
	fread(&scale_, sizeof(Vector2), 1, p_file);
}
