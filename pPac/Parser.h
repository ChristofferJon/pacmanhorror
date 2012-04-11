#ifndef __PARSER__
#define __PARSER__

#include "ParserLib.h"
#include "Ini_Util.h"

class Parser
{
public:
	Parser();
	~Parser();

public:
	static Parser*	Instance();
	void			Load( std::string _name );

	std::string getStringOfKey(const std::string &key) const;
	int			getIntOfKey(const std::string &key) const;
	bool		getBoolOfKey(const std::string &key) const;

private:
	std::map<std::string, std::string>	contents;
	
	void		removeComment(std::string &line) const;
	bool		onlyWhitespace(const std::string &line) const;
	bool		validLine(const std::string &line)const;
	void		extractKey(std::string &key, size_t const &sepPos, const std::string &line)const;
	void		extractValue(std::string &value, size_t const &sepPos, const std::string &line)const;
	void		extractContents(const std::string &line);
	void		parseLine(const std::string &line, size_t const lineNo);

	void		extractKeys();
	bool		keyExists(const std::string &key) const;

	Ini_Util* iniU;
};

#endif