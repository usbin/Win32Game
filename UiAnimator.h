#pragma once
#include "Animator.h"
class UiAnimator : public Animator
{
	// Animator��(��) ���� ��ӵ�
	virtual void CreateAnimation(const tstring& name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset, float duration, int img_count, bool is_repeat) override;

	// Animator��(��) ���� ��ӵ�
	virtual void SaveToFile(FILE* p_file) override;
	virtual void LoadFromFile(FILE* p_file) override;
};

