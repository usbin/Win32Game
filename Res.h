#pragma once
#include "global.h"

class Res
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


};

