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
	Vector2 pos_offset_;		//속한 오브젝트의 pos를 기준으로 한 오프셋
	Vector2 scale_;				//크기
	Vector2 final_pos_;			//FinalUpdate에서 업데이트하는 pos
	GObject* owner_;			//속한 오브젝트

	bool is_physical_collider_;	//물리법칙에 적용을 받는가(충돌 검사만 하는가, 충돌시 이동을 제한하는가)
	std::vector<Collider*> physical_collisions_;
	

public:
	inline UINT get_id() { return id_; };
	inline void set_pos_offset(Vector2 pos) { pos_offset_ = pos; };
	inline Vector2 get_pos_offset() { return pos_offset_; };
	inline void set_scale(Vector2 scale) { scale_ = scale; };
	inline Vector2 get_scale() { return scale_; };
	inline void set_owner(GObject* owner) { owner_ = owner; };
	inline GObject* get_owner() const { return owner_; };
	inline Vector2 get_pos() { return final_pos_; };
	inline void set_is_physical_collider(bool b) { is_physical_collider_ = b; };
	inline bool get_is_physical_collider() { return is_physical_collider_; };
	inline const std::vector<Collider*>& get_physical_collisions() { return physical_collisions_; };

	void FinalUpdate();		//매 프레임 업데이트가 끝난 후 owner의 위치를 따라감.
	void Render(ID3D11Device* p_d3d_device);

	void OnCollisionEnter(Collider* collider);
	void OnCollisionStay(Collider* collider);
	void OnCollisionExit(Collider* collider);

	Collider& operator=(const Collider& o_c) = delete;


	// ISavable을(를) 통해 상속됨
	virtual void SaveToFile(FILE* p_file) override;
	virtual void LoadFromFile(FILE* p_file) override;

};

