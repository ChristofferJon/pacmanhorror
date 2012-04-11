#ifndef __CFG__
#define __CFG__

#include "CfgLib.h"
#include "CFG_Link.h"
#include "Dbg.h"

#pragma region Class Description

/*	CFG reads and writes .dat files and maps the information to a custom data structure (CFG_Link).
	Each unqiue link acts as a parent node with multiple entries (children) that holds a unqiue 
	'key' and a token 'value'.

	By doing so we can easily create and derive information from files by setting up a directory
	container, pointing to all files we wish to read. Files are accessed upon request and are not
	mapped until that request is made.

	mContainer separates all the unique directories so they can be accessed and treated separately.

	While class CFG is a singleton, it can both hold global data and load active data and then
	discard it. It is up to the discretion of the user.
*/

#pragma endregion

#pragma region Container Struct

struct DATA_CONTAINER
{
private:
	const std::string mName;
	std::vector<CFG_Link*> mLinks;

public:
	DATA_CONTAINER( std::string _name ) : mName(_name)
	{ }

	~DATA_CONTAINER()
	{
		for each (CFG_Link* l in mLinks)
			l->~CFG_Link();
	}

	bool Duplicate(std::string _name)
	{
		for each ( CFG_Link* l in mLinks )
			if ( l->name() == _name )
				return true;		// duplicate exist

		return false;	// unique link
	}

	void addLink(std::string _name)
	{
		if ( !Duplicate( _name ) )
			mLinks.push_back( new CFG_Link( _name ) );
	}

	CFG_Link* getLink(std::string _name)
	{
		for each ( CFG_Link* l in mLinks )
			if ( l->name() == _name )
				return l;

		return NULL;
	}

	std::string name()
	{ 
		return mName; 
	}

	std::vector<CFG_Link*> links()const
	{
		return mLinks;
	}
};

#pragma endregion

class CFG
{
private:
		CFG();

public:
	CFG* getCFG();
	~CFG();

//member variables
private:
	std::vector<DATA_CONTAINER*> mContainers;
	Dbg* dbg;

//public methods
public:	
	void		MapToFile(std::string _file);
	void		ReadFromFile(std::string _file);
	void		RemoveContainerEntry(std::string _file);

	void		ChangeEntry(std::string _key, std::string _value,  std::string _link, std::string _file);
	std::string GetStringOfKey(std::string _key, std::string _link, std::string _file);
	int			GetIntOfKey(std::string _key, std::string _link, std::string _file);
	bool		GetBoolOfKey(std::string _key, std::string _link, std::string _file);
	float		GetFloatOfKey(std::string _key, std::string _link, std::string _file);

//private methods
private:
	//read/write
	void		WriteTemplate();
	void		MapDirectories(std::string _baseFile);

	//cleaning
	void		RemoveComment(std::string &line);
	bool		IsWhiteSpace(std::string &line);

	//validation
	bool		Duplicate(std::string _file);
	bool		IsLink(std::string &line);
	bool		ValidLine(std::string &line);
	bool		KeyExists(std::string &_key, std::string _link, std::string _file);

	//extraction
	void		ParseLine(std::string &line, size_t lineNo, std::string &_link, std::string _file);
	void		ExtractContent(std::string &line, std::string &_link, std::string _file);
	void		ExtractKey(std::string &key, size_t &sepPos, std::string &line);
	void		ExtractValue(std::string &value, size_t &sepPos, std::string &line);
	
	//get/set
	DATA_CONTAINER*		GetContainer(std::string _name);	
	CFG_Entry*			GetEntry(std::string _key, std::string _link, std::string _file);
};

#endif