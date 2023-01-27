#include "FmodSound.h"
#include "Sound.h"
FmodSound::FmodSound() {};
FmodSound::~FmodSound() {};
void FmodSound::Init()
{
	memset(channels_, 0, sizeof(channels_));

	if (FMOD_System_Create(&fmod_system_, FMOD_VERSION) != FMOD_RESULT::FMOD_OK) return;
	if (FMOD_System_Init(fmod_system_, 32, FMOD_INIT_NORMAL, nullptr) != FMOD_RESULT::FMOD_OK) return;




}

void FmodSound::Update()
{
	if (!fmod_system_) return;

	FMOD_System_Update(fmod_system_);
	for (int i = 0; i < 32; i++) {
		if (channels_[i].repeat) {
			FMOD_BOOL is_playing = 0;
			FMOD_Channel_IsPlaying(channels_[i].channel, &is_playing);
			if (!is_playing) {
				Play(i, channels_[i].sound, true);
			}
		}
	}

}

FMOD_SOUND* FmodSound::CreateFmodSound(const tstring& absolute_path)
{
	FMOD_MODE mode = 0;
	mode |= FMOD_LOOP_OFF;

	FMOD_SOUND* fmod_sound = nullptr;

	std::string str = TstringToString(absolute_path);

	FMOD_System_CreateSound(fmod_system_, str.c_str(), mode, nullptr, &fmod_sound);
	return fmod_sound;

}

void FmodSound::PlayBackground(Sound* sound)
{
	StopBackground();
	Play(CHANNEL_BACKGROUND, sound, true);
}

void FmodSound::PlayAmbience(Sound* sound)
{
	StopAmbience();
	Play(CHANNEL_AMBIENCE, sound, true);
}
void FmodSound::Play(int channel, Sound* sound, bool repeat)
{
	if (channel >= 0 && channel < 32) {
		channels_[channel].sound = sound;
		channels_[channel].repeat = repeat;
		FMOD_System_PlaySound(fmod_system_, sound->get_fmod_sound(), NULL, false, &(channels_[channel].channel));

	}
}

void FmodSound::PlayStep(Sound* sound)
{
	FMOD_BOOL is_playing = 0;
	FMOD_Channel_IsPlaying(channels_[CHANNEL_STEP].channel, &is_playing);
	if(!is_playing)
		Play(CHANNEL_STEP, sound, false);
}

void FmodSound::StopBackground()
{
	Stop(CHANNEL_BACKGROUND);
}
void FmodSound::StopAmbience()
{
	Stop(CHANNEL_AMBIENCE);
}

void FmodSound::Stop(int channel)
{
	FMOD_Channel_SetPaused((channels_[channel].channel), true);
}

int FmodSound::GetChannel()
{
	for (int i = 3; i < 32; i++) {
		if (!channels_[i].channel) {
			return i;
		}
		else {
			FMOD_BOOL is_playing = 0;
			FMOD_Channel_IsPlaying(channels_[i].channel, &is_playing);

			if (!channels_[i].repeat && !is_playing) {
				return i;
			}
		}
		
	}
	return -1;
}

void FmodSound::OnDestroy()
{
	FMOD_System_Release(fmod_system_);
	fmod_system_ = nullptr;
}
