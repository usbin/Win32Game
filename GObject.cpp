#include "GObject.h"
#include "Collider.h"
#include "Animator.h"
#include "UiSprite.h"
#include "RealObjectSprite.h"

unsigned int GObject::id_counter_ = 1;
GObject::GObject()
	: name_(_T(""))
	, pos_(Vector2{0,0})
	, scale_(Vector2{ 0,0 })
	, id_(id_counter_++)
	, group_type_(GROUP_TYPE::DEFAULT)
	, is_dead_(false)
	, visible_(true){

}
GObject::GObject(const GObject& origin) //복사 생성자
	: name_(_T(""))
	, pos_(origin.pos_)
	, scale_(origin.scale_)
	, id_(id_counter_++)
	, group_type_(origin.group_type_)
	, is_dead_(false)
	, visible_(true){
}
GObject::~GObject(){
}

void GObject::SaveToFile(FILE* p_file)
{

	int name_size = get_name().size() + 1;
	fwrite(&name_size, sizeof(UINT), 1, p_file);
	fwrite(get_name().c_str(), sizeof(TCHAR), name_size, p_file);
	fwrite(&pos_, sizeof(Vector2), 1, p_file);
	fwrite(&scale_, sizeof(Vector2), 1, p_file);
	fwrite(&group_type_, sizeof(GROUP_TYPE), 1, p_file);
	fwrite(&visible_, sizeof(bool), 1, p_file);
	fwrite(&direction_, sizeof(DIRECTION), 1, p_file);

}

void GObject::LoadFromFile(FILE* p_file)
{
	int name_size;
	fread(&name_size, sizeof(UINT), 1, p_file);
	TCHAR* name = new TCHAR[name_size];
	fread(name, sizeof(TCHAR), name_size, p_file);
	name_ = name;
	delete[] name;
	fread(&pos_, sizeof(Vector2), 1, p_file);
	fread(&scale_, sizeof(Vector2), 1, p_file);
	fread(&group_type_, sizeof(GROUP_TYPE), 1, p_file);
	fread(&visible_, sizeof(bool), 1, p_file);
	fread(&direction_, sizeof(DIRECTION), 1, p_file);
	
}

