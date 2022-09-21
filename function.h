#pragma once
#include "global.h"

class GObject;

float DtF();

void CreateGObject(GObject* object, GROUP_TYPE type);
void DeleteGObject(GObject* object, GROUP_TYPE type);
void ChangeScene(SCENE_TYPE scene_type);

Vector2 GetRenderPos(Vector2 world_pos);
Vector2 GetWorldPos(Vector2 render_pos);

template <typename T>
void SafeDeleteVector(std::vector<T>& cont) {
	for (auto item : cont) {
		delete item;
	}
	cont.clear();
}

template <typename T1, typename T2>
void SafeDeleteMap(std::map<T1, T2>& map) {
	for (auto pair : map) {
		delete pair.second;
	}
	map.clear();
}
