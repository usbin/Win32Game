#include "Sound.h"
#include "FmodSound.h"
#include "PathManager.h"
Sound::Sound()
{
}
Sound::~Sound()
{

}
void Sound::Load()
{
	tstring sound_path = PathManager::GetInstance()->GetContentPath() + get_relative_path();

	fmod_sound_ = FmodSound::GetInstance()->CreateFmodSound(sound_path);
}
