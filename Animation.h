#pragma once
#include "global.h"
#include "ISavable.h"
class Texture;
class Animator;
struct AnimationFrame {
	Vector2 base_pos;
	Vector2 img_size;
};
class Animation : public ISavable
{
public:
	Animation();
	~Animation();
private:
	tstring name_;
	Texture* texture_;
	float duration_;
	bool is_repeat_;		//�ݺ���� ����
	Animator* animator_;
	int img_count_;
	Vector2 offset_;		//GObject�� ���� �׷����� �ִϸ��̼ǰ��� �Ÿ�
	bool is_finished_;		//����� �������� ����

	float frame_acc_dt_;	//���� ������ ���� �� ����� �ð�
	int frame_index_;

	std::vector<AnimationFrame> frames_;

public:
	void Init(tstring name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset
		, float duration, int img_count, bool is_repeat);
	void Update();
	void Render(HDC hdc);
	void ResetFrame();	//�������� 0��°�� �ǵ����� �Լ�(�����)
	inline void set_animator(Animator* animator) { animator_ = animator; };
	inline tstring& get_name() { return name_; };
	inline bool is_repeat() { return is_repeat_; };
	inline bool is_finished() { return is_finished_; };
	

	// ISavable��(��) ���� ��ӵ�
	virtual void SaveToFile(FILE* p_file) override;

	virtual void LoadFromFile(FILE* p_file) override;

};

