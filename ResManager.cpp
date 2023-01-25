#include "ResManager.h"
#include "Texture.h"
#include "DXClass.h"
#include "Sound.h"
ResManager::ResManager() {}

ResManager::~ResManager() {
    for (auto pair : textures_) {
        delete pair.second;
    }
    textures_.clear();

    for (auto pair : sounds_) {
        delete pair.second;
    }
    sounds_.clear();
}

Texture* ResManager::LoadTexture(const tstring& key, const tstring& relative_path)
{
    
    auto it = textures_.find(key);
    if (it != textures_.end()) {
        return it->second;
    }
    Texture* texture = DEBUG_NEW Texture();
    texture->set_key(key);
    texture->set_relative_path(relative_path);
    texture->Load();
    textures_.insert(std::make_pair(key, texture));

    return texture;

}

Sound* ResManager::LoadSound(const tstring& key, const tstring& relative_path)
{
    auto it = sounds_.find(key);
    if (it != sounds_.end()) {
        return it->second;
    }
    Sound* sound = DEBUG_NEW Sound();
    sound->set_key(key);
    sound->set_relative_path(relative_path);
    sound->Load();
    sounds_.insert(std::make_pair(key, sound));

    return sound;
}
