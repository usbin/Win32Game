#pragma once
#include "global.h"
#include "Res.h"
class Sound : public Res
{
private:
	Sound();
	~Sound();

	FMOD_SOUND* fmod_sound_;
	void Load();
public:
	FMOD_SOUND* get_fmod_sound() { return fmod_sound_; };

	friend class ResManager;
};

