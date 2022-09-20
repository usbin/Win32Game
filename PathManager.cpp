#include "pch.h"
#include "PathManager.h"

PathManager::PathManager()
	: content_path_(_T("")) {

}
PathManager::~PathManager() {}

void PathManager::Init()
{
	TCHAR current_dir[255] = _T("");
	GetCurrentDirectory(255, current_dir);
	//bin또는 bin_debug를 지우고 \bin\content\를 새로 붙임.
	size_t len = _tcslen(current_dir);
	for (size_t i = len - 1; i >= 0; i--) {
		if (current_dir[i] == '\\') {
			current_dir[i] = '\0';
			break;
		}
	}
	_tcsncat_s(current_dir, _T("\\bin\\content\\"), _tcslen(_T("\\bin\\content\\")));
	content_path_ = tstring(current_dir);

}

const tstring& PathManager::GetContentPath()
{
	return content_path_;

}
