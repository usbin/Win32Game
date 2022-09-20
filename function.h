#pragma once

class GObject;

void CreateGObject(GObject* object, GROUP_TYPE type);
void DeleteGObject(GObject* object, GROUP_TYPE type);
void ChangeScene(SCENE_TYPE scene_type);

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
float DtF();