#ifndef __CFG_LINK__
#define __CFG_LINK__

#include "CFG_Entry.h"
#include <vector>

class CFG_Link
{
public:
	CFG_Link(std::string _name);
	~CFG_Link();

private:
	const std::string		mName;
	std::vector<CFG_Entry*>	mEntries;

public:
	std::string		name()const;
	CFG_Entry*		getEntry(std::string _key);
	std::string		getEntryValue(std::string _key)const;
	void			addEntry(std::string _key, std::string _value);
	bool			Duplicate(std::string _key);

	std::vector<CFG_Entry*> entries()const;
};

#endif