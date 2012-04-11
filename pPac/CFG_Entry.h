#ifndef __CFG_ENTRY__
#define __CFG_ENTRY__

#include <string>

class CFG_Entry
{
public:
	CFG_Entry(std::string _key, std::string _value);
	~CFG_Entry();

private:
	const std::string	mKey;
	std::string	mValue;

public:
	std::string			key()const;
	std::string			value();
};

#endif