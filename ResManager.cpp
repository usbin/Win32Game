#include "ResManager.h"
#include "Texture.h"
#include "DXClass.h"

ResManager::ResManager() {}

ResManager::~ResManager() {
    for (auto it : textures_) {
        delete it.second;
    }
    textures_.clear();
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
