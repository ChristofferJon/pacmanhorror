#include "CFG.h"

CFG* instance = NULL;

//-------------------------
// constructor, destructor
// & getter()
//-------------------------
#pragma region Initialization

CFG::CFG()
{
	MapDirectories(".\\Init\\InitFiles.dat");	// read all initial files directories
	
	if ( GetContainer( "Setup" ) == NULL)		// if no setup.dat exist, create a bare template
		WriteTemplate();

	for each (DATA_CONTAINER* d in mContainers)
		ReadFromFile( d->name() );

	for each ( DATA_CONTAINER* d in mContainers)
	{
		dbg->getDbg()->print("%s\n", d->name().c_str());
		for each ( CFG_Link* l in d->links())
		{
			dbg->getDbg()->print("%s:\n", l->name().c_str());
			for each ( CFG_Entry* e in l->entries())
				dbg->getDbg()->print("\t%s = %s\n", e->key().c_str(), e->value().c_str());
		}
	}
}

CFG::~CFG()
{

}

CFG* CFG::getCFG()
{
	if (instance == NULL)
		instance = new CFG();

	return instance;
}

// default setup template
void CFG::WriteTemplate()
{
	GetContainer("Setup")->addLink("GFX");
	GetContainer("Setup")->addLink("SFX");
	GetContainer("Setup")->addLink("SFX");	//check duplicate issue

	GetContainer("Setup")->getLink("GFX")->addEntry("RESX", "800");
	GetContainer("Setup")->getLink("GFX")->addEntry("RESY", "600");
	GetContainer("Setup")->getLink("GFX")->addEntry("SCREENMODE", "1");

	GetContainer("Setup")->getLink("SFX")->addEntry("MASTER_VOLUME", "100");
	GetContainer("Setup")->getLink("SFX")->addEntry("FX_VOLUME", "100");
	GetContainer("Setup")->getLink("SFX")->addEntry("MUSIC_VOLUME", "100");
	GetContainer("Setup")->getLink("SFX")->addEntry("SFX_ON", "1");

	MapToFile("Setup");
}

#pragma endregion

//-------------------------------------------
// Read/Write to specified file or structure
//-------------------------------------------
#pragma region Data Mapping & Reading

/*	Read all active file directories from master file.
	Each entry is added to mContainers so each directory
	maintains independent links and directories
*/
void CFG::MapDirectories(std::string _baseFile)
{
	std::string line;

	std::ifstream inFile( _baseFile );

	if ( !inFile )
		dbg->getDbg()->print("%s %s %s %s\n", "CFG:\t", "Base directory", _baseFile.c_str(), "does not exist!");
	else
		dbg->getDbg()->print("%s %s %s %s\n", "CFG:\t", "Base directory", _baseFile.c_str(), "found");

	if ( inFile)
	{
		while ( getline( inFile, line ) )
		{
			std::string temp = line;

			if ( temp.empty() || IsWhiteSpace( temp ) )	// nothing of value, just note lineNo
				continue;

			if ( IsLink( line ) && !Duplicate( line ) )	// note current Link and add to list if not duplicate
					mContainers.push_back( new DATA_CONTAINER( line ) );
		}
	}
}

/*	Write all links and subsequent entries to specified file
	(if it exists). dat-file will be formatted correctly but
	any previous comment in the file will be lost.	*/
void CFG::MapToFile(std::string _file)
{
	std::ofstream outFile( ".\\Init\\" + _file + ".dat" );

	if ( !outFile )
		dbg->getDbg()->print("%s %s %s\n", "CFG:\t", _file.c_str(), "file does not exist!");
	else
		dbg->getDbg()->print("%s %s %s\n", "CFG:\t", _file.c_str(), "found");

	if ( outFile )
	{
		for each ( CFG_Link* l in GetContainer(_file)->links() )	// write Link
		{
			outFile << "#" << l->name() << "\n";

			for each ( CFG_Entry* e in l->entries() )	// and write all entries for each link
				outFile << e->key() << " = " << e->value() << " ;\n";
		}
	}

	outFile.close();
}

/*	Read and subsequently map all links and entries from 
	specified file. Automatically differentiates links
	and entries. A temporary link is upheld to map entries
	to correct link.
*/
void CFG::ReadFromFile(std::string _file)
{
	std::ifstream inFile( ".\\Init\\" + _file + ".dat");
	std::string line;
	std::string tempLink;
	size_t lineNo = 0;

	if ( !inFile )
		dbg->getDbg()->print("%s %s %s\n", "CFG:\t", _file.c_str(), "does not exist!");
	else
		dbg->getDbg()->print("%s %s %s\n", "CFG:\t", _file.c_str(), "found");

	if ( inFile )
	{
		while ( getline ( inFile, line ) )
		{
			lineNo++;
			std::string temp = line;

			if ( temp.empty() || IsWhiteSpace( temp ) )	// nothing of value
				continue;

			if ( IsLink( line ) )	// note current Link and add to list
			{
				tempLink = line;
				GetContainer(_file)->addLink( line );
			}
			else					// an entry to the current Link has been found
			{
				RemoveComment( temp );	// find comments and remove them
				ParseLine( temp, lineNo, tempLink, _file );
			}
		}
	}

	inFile.close();
}

#pragma endregion

//----------------------------------------------
// Nitty gritty cleaning of each candidate line
//----------------------------------------------
#pragma region LineParsing

/*	search for end token and erase remaining line	*/
void CFG::RemoveComment(std::string &line)
{
	if ( line.find( ';' != line.npos ) )
		line.erase( line.find( ';' ) );
}

/*	check if white space	*/
bool CFG::IsWhiteSpace(std::string &line)
{
	return ( line.find_first_not_of( ' ' ) == line.npos );
}

/*	search for link token	*/
bool CFG::IsLink(std::string &line)
{
	if ( line[0] == '#' )
	{
		line.erase( line.find( '#' ), 1 );
		return true;
	}
	return false;
}

/*	search for key and value in candidate line	*/
bool CFG::ValidLine(std::string &line)
{
	std::string temp = line;
	temp.erase(0, temp.find_first_not_of( "\t " ) );		// erase any indents

	if ( temp[0] == '=' )	// failed assertion, no key to supposed value
		return false;

	for ( size_t i = temp.find( '=' ) + 1; i < temp.length(); i++)	// check if '=' is separated from key and value
		if ( temp[i] != ' ')
			return true;

	return false;
}

#pragma endregion

//--------------------------
// Validation of candidates
//--------------------------
#pragma region Content Validation

bool CFG::Duplicate(std::string _file)
{
	bool isDuplicate = false;

	for each (DATA_CONTAINER* d in mContainers)
		if (d->name() == _file)
		{
			isDuplicate = true;
			break;
		}

	return isDuplicate;
}

/*	search for duplicate keys in current link	*/
bool CFG::KeyExists(std::string &_key, std::string _link, std::string _file)
{
	// grab the specified container's link
	std::string tempLink = GetContainer( _file )->getLink( _link )->name();

	if (tempLink == "RDATA")	//change
		return false;

	for each ( CFG_Entry* e in GetContainer( _file )->getLink( tempLink )->entries() )
		if ( e->key() == _key )
			return true;

	return false;
}

/*	check the candidate line and if deemed valid,
	extract its contents	*/
void CFG::ParseLine(std::string &line, size_t lineNo, std::string &_link, std::string _file)
{
	if ( line.find( '=' ) == line.npos )
		return;
	if ( !ValidLine( line ) )
		return;

	ExtractContent( line, _link, _file );
}

/*	find the separator token ('=') to extract key and value.
	finally check if the key already exists in the current link	*/
void CFG::ExtractContent(std::string &line, std::string &_link, std::string _file)
{
	std::string temp = line;
	temp.erase(0, temp.find_first_not_of( "\t" ) );
	size_t sepPos = temp.find( '=' );

	std::string key, value;
	ExtractKey( key, sepPos, temp );
	ExtractValue( value, sepPos, temp );

	if( !KeyExists( key, _link, _file ) )		// make sure no identical key exists within that link
		GetContainer(_file)->getLink( _link )->addEntry( key, value );
}

/*	map the key to the param and clean it	*/
void CFG::ExtractKey(std::string &key, size_t &sepPos, std::string &line)
{
	key = line.substr( 0, sepPos );		//key located before '='

	if (key.find( '\t' ) != line.npos || key.find(' ') != line.npos)	// erase all blank spaces
		key.erase( key.find_first_of( "\t " ) );
}

/*	map the value to the param and clean it	*/
void CFG::ExtractValue(std::string &value, size_t &sepPos, std::string &line)
{
	value = line.substr( sepPos + 1 );		// value located after '='

	value.erase(0, value.find_first_not_of( "\t " ) );		// erase all blank spaces
	value.erase( value.find_last_not_of ( "\t " ) + 1 );
}

/*	find the container of specified file	*/
DATA_CONTAINER* CFG::GetContainer(std::string _file)
{
	for (int i = 0; i < mContainers.size(); i++)
		if ( mContainers[i]->name() == _file)
			return mContainers[i];

	return NULL;
}

#pragma endregion

//---------------------
// getters, setters &
// cleaners
//---------------------
#pragma region Misc

/*	return existing entry	*/
CFG_Entry* CFG::GetEntry(std::string _key, std::string _link, std::string _file)
{
	DATA_CONTAINER* temp = GetContainer(_file);

	if (temp != NULL)
	{
		for each (CFG_Entry* e in temp->getLink( _link )->entries() )	// search through specified link's entries
		{
			if ( e->key() == _key )		// if key exists, remap value (note, should probably call MapToFile() as well to ensure continuity
				return e;
		}
	}
	else return NULL;
}

/*	change an existing entry's value	*/
void CFG::ChangeEntry(std::string _key, std::string _value, std::string _link, std::string _file)
{
	CFG_Entry* temp = GetEntry(_key, _link, _file);

	if (temp != NULL)
		temp->value() = _value;
}

/*	extract entry value as string	*/
std::string CFG::GetStringOfKey(std::string _key, std::string _link, std::string _file)
{
	CFG_Entry* temp = GetEntry(_key, _link, _file);

	if (temp != NULL)
		return temp->value();
	
	return "Invalid";
}

/*	extract entry value as int	*/
int CFG::GetIntOfKey(std::string _key, std::string _link, std::string _file)
{
	CFG_Entry* temp = GetEntry(_key, _link, _file);
	int validate;

	if (temp != NULL)
	{
		try {	validate = atoi( temp->value().c_str() );	}
		catch (std::exception e) {	return NULL; }
	}
	
	return validate;
}

/*	extract entry value as float	*/
float CFG::GetFloatOfKey(std::string _key, std::string _link, std::string _file)
{
	CFG_Entry* temp = GetEntry(_key, _link, _file);
	float validate;

	if (temp != NULL)
	{
		try {	validate = atof( temp->value().c_str() );	}
		catch (std::exception e) {	return NULL; }
	}
	
	return validate;
}

/*	extract entry value as bool	*/
bool CFG::GetBoolOfKey(std::string _key, std::string _link, std::string _file)
{
	CFG_Entry* temp = GetEntry(_key, _link, _file);

	if (temp != NULL)
	{
		int validate = atoi( temp->value().c_str() );

		if (validate == 0 || validate == 1 )
			return (BOOL)validate;
	}

	return NULL;
}

/*	remove specified container entry. Use only for local 
	data that only needs to be accessed once or during
	low time	*/
void CFG::RemoveContainerEntry(std::string _file)
{
	for each (DATA_CONTAINER* d in mContainers)
		if ( d->name() == _file )
		{
			d->~DATA_CONTAINER();
			break;
		}
}

#pragma endregion