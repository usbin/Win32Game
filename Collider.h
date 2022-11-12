#pragma once
#include "global.h"
#include "ISavable.h"
class GObject;

class Collider : public ISavable
{
public:
	Collider();
	~Collider();
	Collider(const Collider& org);

private:
	static UINT id_counter_;
	UINT id_;
	Vector2 pos_offset_;	//속한 오브젝트의 pos를 기준으로 한 오프셋
	Vector2 scale_;			//크기
	Vector2 final_pos_;		//FinalUpdate에서 업데이트하는 pos
	GObject* owner_;		//속한 오브젝트
	int collision_count_;

public:
	inline UINT get_id() { return id_; };
	inline void set_pos_offset(const Vector2& pos) { pos_offset_ = pos; };
	inline const Vector2& get_pos_offset() { return pos_offset_; };
	inline void set_scale(const Vector2& scale) { scale_ = scale; };
	inline const Vector2& get_scale() { return scale_; };
	inline void set_owner(GObject* owner) { owner_ = owner; };
	inline const Vector2& get_pos() { return final_pos_; };

	void FinalUpdate();		//매 프레임 업데이트가 끝난 후 owner의 위치를 따라감.
	void Render(LPDIRECT3DDEVICE9 p_d3d_device);

	void OnCollisionEnter(const Collider& collider);
	void OnCollisionStay(const Collider& collider);
	void OnCollisionExit(const Collider& collider);

	Collider& operator=(const Collider& o_c) = delete;


	// ISavable을(를) 통해 상속됨
	virtual void SaveToFile(FILE* p_file) override;
	virtual void LoadFromFile(FILE* p_file) override;

};

