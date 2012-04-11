#include "CFG_Link.h"

CFG_Link::CFG_Link(std::string _name) : mName(_name)
{
}


CFG_Link::~CFG_Link()
{
	for each ( CFG_Entry* e in mEntries )
		if (e) e->~CFG_Entry();
}

std::string CFG_Link::name()const
{
	return mName;
}

CFG_Entry* CFG_Link::getEntry(std::string _key)
{
	for each ( CFG_Entry* e in mEntries )
		if ( e->key() == _key )
			return e;

	return NULL;
}

std::string CFG_Link::getEntryValue(std::string _key)const
{
	for each ( CFG_Entry* e in mEntries )
		if ( e->key() == _key )
			return e->value();

	return "Invalid";
}

void CFG_Link::addEntry(std::string _key, std::string _value)
{
	if ( !Duplicate(_key) )
		mEntries.push_back( new CFG_Entry( _key, _value ) );
}

bool CFG_Link::Duplicate(std::string _key)
{
	for each ( CFG_Entry* e in mEntries )
		if ( e->key() == _key )
			return true;

	return false;
}

std::vector<CFG_Entry*> CFG_Link::entries()const
{
	return mEntries;
}