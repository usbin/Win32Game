#include "PathManager.h"

PathManager::PathManager()
	: content_path_(_T("")) {

}
PathManager::~PathManager() {}

void PathManager::Init()
{
	TCHAR current_dir[255] = _T("");
	GetCurrentDirectory(255, current_dir);
	//bin�Ǵ� bin_debug�� ����� \bin\content\�� ���� ����.
	int len = static_cast<int>(_tcslen(current_dir));
	for (int i = len - 1; i >= 0; i--) {
		if (current_dir[i] == '\\') {
			current_dir[i] = '\0';
			break;
		}
	}
	TCHAR content_path[255] = _T("");
	_tcsncat_s(content_path, current_dir, _tcslen(current_dir));
	_tcsncat_s(content_path, _T("\\bin\\content\\"), _tcslen(_T("\\bin\\content\\")));
	content_path_ = tstring(content_path);





}

const tstring& PathManager::GetContentPath()
{
	return content_path_;

}
