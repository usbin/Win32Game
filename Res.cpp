#include "Res.h"

Res::Res()
	: key_(_T(""))
	, relative_path_(_T(""))
{
}

Res::~Res()
{
}

void Res::SaveToFile(FILE* p_file)
{
	UINT key_size = key_.size()+1;
	fwrite(&key_size, sizeof(UINT), 1, p_file);
	fwrite(key_.c_str(), sizeof(TCHAR), key_size, p_file);
	UINT path_size = relative_path_.size()+1;
	fwrite(&path_size, sizeof(UINT), 1, p_file);
	fwrite(relative_path_.c_str(), sizeof(TCHAR), path_size, p_file);
}

void Res::LoadFromFile(FILE* p_file)
{
	UINT key_size;
	fread(&key_size, sizeof(UINT), 1, p_file);
	TCHAR* key = new TCHAR[key_size];
	fread(key, sizeof(TCHAR), key_size, p_file);
	key_ = key;
	delete[] key;


	UINT path_size;
	fread(&path_size, sizeof(UINT), 1, p_file);
	TCHAR* path = new TCHAR[path_size];
	fread(path, sizeof(TCHAR), path_size, p_file);
	relative_path_ = path;
	delete[] path;
}
