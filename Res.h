#pragma once
#include "global.h"
#include "ISavable.h"

class Res : public ISavable
{
private :
	tstring key_;
	tstring relative_path_;

public:
	Res();
	virtual ~Res();
	inline const tstring& get_key() { return key_; };
	inline void set_key(const tstring& key) { key_ = key; };
	inline const tstring& get_relative_path() { return relative_path_; };
	inline void set_relative_path(const tstring& path) { relative_path_ = path; };


	// ISavable을(를) 통해 상속됨
	virtual void SaveToFile(FILE* p_file) override;


	// ISavable을(를) 통해 상속됨
	virtual void LoadFromFile(FILE* p_file) override;

};

