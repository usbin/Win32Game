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

	const int CHANNEL_BACKGROUND = 0;//배경음악
	const int CHANNEL_AMBIENCE = 1;	//환경음(낮일 때 새소리, 밤일 때 부엉이 소리 등)
	ChannelInfo channels_[32];
	FMOD_SOUND* CreateFmodSound(const tstring& absolute_path);
	
public:
	
	void Init();
	void Update();

	void PlayBackground(Sound* sound);						//항상 0번 채널에서 재생.
	void PlayAmbience(Sound* sound);						//항상 1번 채널에서 재생.
	void Play(int channel, Sound* sound, bool repeat);		//특정 채널에서 재생.
	void StopBackground();
	void StopAmbience();
	void Stop(int channel);
	int GetChannel();						//비어있는 채널을 리턴. 없으면 nullptr

	void OnDestroy();
	friend class Sound;
	
};

