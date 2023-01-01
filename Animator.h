#pragma once
#include "global.h"
#include "ISavable.h"
#include "Animation.h"
class Animation;
class Texture;
class Animator : public ISavable
{
public:
	Animator();
	Animator(const Animator& origin);
	virtual ~Animator();
protected:
	GObject* owner_;
	std::map<tstring, Animation*> anims_;
	Animation* current_anim_;
public:
	virtual void CreateAnimation(const tstring& name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset
		, float duration, int img_count, bool is_repeat) = 0;
	void Play(const tstring& name);
	void Stop();
	Animation* FindAnimation(const tstring& name);
	bool is_current_playing(const tstring& name);
	void Update();
	virtual void Render(ID3D11Device*  p_d3d_device);

	GObject* get_owner() { return owner_; };
	void set_owner(GObject* owner) { owner_ = owner; };
	inline bool is_finished() { return current_anim_ == nullptr ? true : current_anim_->is_finished(); };
private :


	friend class RealObject;



	// ISavable을(를) 통해 상속됨
	virtual void SaveToFile(FILE* p_file);

	virtual void LoadFromFile(FILE* p_file);

};

