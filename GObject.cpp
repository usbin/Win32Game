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
