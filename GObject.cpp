#include "GObject.h"
#include "Collider.h"
#include "Animator.h"
#include "Sprite.h"

unsigned int GObject::id_counter_ = 1;
GObject::GObject()
	: name_(_T(""))
	, pos_(Vector2{0,0})
	, scale_(Vector2{ 0,0 })
	, id_(id_counter_++)
	, group_type_(GROUP_TYPE::DEFAULT)
	, is_dead_(false)
	, sprite_(nullptr){

}
GObject::GObject(const GObject& origin) //복사 생성자
	: name_(_T(""))
	, pos_(origin.pos_)
	, scale_(origin.scale_)
	, id_(id_counter_++)
	, group_type_(origin.group_type_)
	, is_dead_(false)
	, sprite_(nullptr){
	//sprite 복사해야함.
}
GObject::~GObject(){
	if(sprite_) delete sprite_;
}

void GObject::ChangeSprite(Sprite* sprite)
{
	if (sprite_) delete sprite_;
	sprite_ = sprite;
}

void GObject::SaveToFile(FILE* p_file)
{
	UINT name_size = name_.size()+1;
	fwrite(&name_size, sizeof(UINT), 1, p_file);
	fwrite(name_.c_str(), sizeof(TCHAR), name_size, p_file);
	fwrite(&pos_, sizeof(Vector2), 1, p_file);
	fwrite(&scale_, sizeof(Vector2), 1, p_file);
	fwrite(&group_type_, sizeof(GROUP_TYPE), 1, p_file);
	fwrite(&sprite_, sizeof(DWORD_PTR), 1, p_file);
	if (sprite_) {
		sprite_->SaveToFile(p_file);
	}

}

void GObject::LoadFromFile(FILE* p_file)
{
	UINT name_size;
	fread(&name_size, sizeof(UINT), 1, p_file);
	TCHAR* name = new TCHAR[name_size];
	fread(name, sizeof(TCHAR), name_size, p_file);
	name_ = name;
	delete[] name;
	fread(&pos_, sizeof(Vector2), 1, p_file);
	fread(&scale_, sizeof(Vector2), 1, p_file);
	fread(&group_type_, sizeof(GROUP_TYPE), 1, p_file);
	fread(&sprite_, sizeof(DWORD_PTR), 1, p_file);
	if (sprite_) {
		sprite_ = new Sprite();
		sprite_->LoadFromFile(p_file);
		sprite_->set_owner(this);
	}
	
}

