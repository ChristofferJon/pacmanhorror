#ifndef __INI_UTIL__
#define __INI_UTIL__

#include "ParserLib.h"

class Ini_Util
{
private:
	Ini_Util();
	~Ini_Util();

public:
	static Ini_Util*	Instance();


	std::string		GetFileByIndex(int _index);
	std::string		GetFileByName(std::string _name);


private:
	void		Load(LPCSTR _iniDirectories);
	int			numEntries;
	bool		CheckValidity(std::string _file);
	bool		CheckDuplicate(std::string _entry);
	LPCSTR		mIniDirs;

	std::vector<std::string>	mIniFiles;
	const LPCSTR			mDir;
};

#endif