#include "Ini_Util.h"

#pragma region Initialization

Ini_Util* instance = NULL;

Ini_Util::Ini_Util() : mDir(".\\Init\\iniDirs.txt")
{
	numEntries = 0;
}


Ini_Util::~Ini_Util()
{
}

Ini_Util* Ini_Util::Instance()
{
	if (instance == NULL)
	{
		instance = new Ini_Util();
		instance->Load( instance->mDir );
	}

	return instance;
}

// load all active directory files
void Ini_Util::Load(LPCSTR _iniDirectories)
{
	WCHAR line[256] = { 0 };
	std::wifstream inFile ( _iniDirectories );

	while(inFile)
	{
		inFile >> line;

		if( wcscmp( line, L"#") == 0)
		{
			inFile >> line;
			std::wstring temp(line);
			std::string dirCandidate(temp.begin(), temp.end());

			//if( CheckValidity(dirCandidate) == true)
				instance->mIniFiles.push_back(dirCandidate);
		}
	}
	inFile.close();

	instance->numEntries = instance->mIniFiles.size();
}

#pragma endregion

#pragma region Private Methods

// check to see if file exist
bool Ini_Util::CheckValidity( std::string _file )
{
	std::wifstream inFile( ".\\Init\\" + _file );

	if (!inFile)
	{
		inFile.close();
		return false;
	}

	inFile.close();
	return CheckDuplicate( _file );
}

// check to see if entry is duplicate
bool Ini_Util::CheckDuplicate( std::string _entry )
{
	bool noDuplicate = true;

	for each ( std::string s in mIniFiles )
		if (_entry == s)
		{
			noDuplicate = false;		// no need to check further
			break;			
		}

	return noDuplicate;
}

#pragma endregion

#pragma region Public Methods

std::string Ini_Util::GetFileByIndex(int _index)
{
	if (_index >= 0 && _index < instance->numEntries)
		return instance->mIniFiles[_index];

	else return "Invalid Entry";
}

std::string Ini_Util::GetFileByName(std::string _name)
{
	for each (std::string s in instance->mIniFiles)
		if (_name == s)
			return s;

	return "Invalid Entry";
}

#pragma endregion