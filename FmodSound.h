#pragma once
#include "global.h"

class Sound;
struct ChannelInfo {
	FMOD_CHANNEL* channel;
	Sound* sound;
	bool repeat;
};

class FmodSound
{
	SINGLETON(FmodSound);
private:

	FMOD_SYSTEM* fmod_system_ =	nullptr;

	const int CHANNEL_BACKGROUND = 0;//�������
	const int CHANNEL_AMBIENCE = 1;	//ȯ����(���� �� ���Ҹ�, ���� �� �ξ��� �Ҹ� ��)
	ChannelInfo channels_[32];
	FMOD_SOUND* CreateFmodSound(const tstring& absolute_path);
	
public:
	
	void Init();
	void Update();

	void PlayBackground(Sound* sound);						//�׻� 0�� ä�ο��� ���.
	void PlayAmbience(Sound* sound);						//�׻� 1�� ä�ο��� ���.
	void Play(int channel, Sound* sound, bool repeat);		//Ư�� ä�ο��� ���.
	void StopBackground();
	void StopAmbience();
	void Stop(int channel);
	int GetChannel();						//����ִ� ä���� ����. ������ nullptr

	void OnDestroy();
	friend class Sound;
	
};

