#include "CFG_Entry.h"


CFG_Entry::CFG_Entry(std::string _key, std::string _value) : mKey(_key), mValue(_value)
{

}


CFG_Entry::~CFG_Entry()
{

}

std::string CFG_Entry::key()const
{
	return mKey;
}

std::string CFG_Entry::value()
{
	return mValue;
}