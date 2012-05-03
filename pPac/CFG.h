#ifndef __CFG__
#define __CFG__

#include "CfgLib.h"
#include "CFG_Link.h"
#include "Dbg.h"

using std::string;

#pragma region Class Description

/*	CFG reads and writes .dat files and maps the information to a custom data structure (CFG_Link).
	Each unqiue link acts as a parent node with multiple entries (children) that holds a unqiue 
	'key' and a token 'value'.

	By doing so we can easily create and derive information from files by setting up a directory
	container, pointing to all files we wish to read. Files are accessed upon request and are not
	mapped until that request is made.

	mContainer separates all the unique directories so they can be accessed and treated separately.

	While class CFG is a singleton, it can both hold global data and load active data and then
	discard it. It is up to the discretion of the user.	This way the user can choose to keep
	specific data at all times while adding/subtracting various other data at command, or just
	flush out all the data and start fresh.	*/

#pragma endregion

/* data holder of links and linked entries	*/
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
				return true;		// duplicate link exist

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
	void		MapToFile(string _file);
	void		ReadFromFile(string _root, string _file);
	void		RemoveContainerEntry(string _file);

	void		ChangeEntry(string _key, string _value,  string _link, string _file);
	std::string GetStringOfKey(string _key, string _link, string _file);
	int			GetIntOfKey(string _key, string _link, string _file);
	bool		GetBoolOfKey(string _key, string _link, string _file);
	float		GetFloatOfKey(string _key, string _link, string _file);

	void		MapDirectories(string _root, string _baseFile);

//private methods
private:
	//read/write
	void		WriteTemplate();
	

	//cleaning
	void		RemoveComment(string &line);
	bool		IsWhiteSpace(string &line);

	//validation
	bool		Duplicate(string _file);
	bool		IsLink(string &line);
	bool		ValidLine(string &line);
	bool		KeyExists(string &_key, string _link, string _file);

	//extraction
	void		ParseLine(string &line, size_t lineNo, string &_link, string _file);
	void		ExtractContent(string &line, string &_link, string _file);
	void		ExtractKey(string &key, size_t &sepPos, string &line);
	void		ExtractValue(string &value, size_t &sepPos, string &line);
	
public:
	//get/set
	DATA_CONTAINER*		GetContainer(string _name);	
	CFG_Entry*			GetEntry(string _key, string _link, string _file);
};

#endif