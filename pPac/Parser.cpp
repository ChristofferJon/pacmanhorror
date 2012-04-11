#include "Parser.h"

Parser::Parser()
{
	iniU->Instance();
}


Parser::~Parser()
{
}

void Parser::Load( std::string _name )
{
	
	std::ifstream file;
	file.open((".\\Init\\" + iniU->GetFileByName(_name)).c_str());

	if (!file)
	{
		file.close();
		return;
	}

	std::string line;
	size_t lineNo = 0;
	while(std::getline(file, line))
	{
		lineNo++;
		std::string temp = line;

		if (temp.empty())
			continue;

		removeComment(temp);

		if (onlyWhitespace(temp))
			continue;

		parseLine(temp, lineNo);
	}

	file.close();
}

void Parser::removeComment(std::string &line) const
{
	if (line.find(';' != line.npos))
		line.erase(line.find(';'));
}

bool Parser::onlyWhitespace(const std::string &line) const
{
	return (line.find_first_not_of(' ') == line.npos);
}

bool Parser::validLine(const std::string &line) const
{
	std::string temp = line;
	temp.erase(0, temp.find_first_not_of("\t "));

	if (temp[0] == '=')
		return false;

	for (size_t i = temp.find('=') + 1; i < temp.length(); i++)
		if (temp[i] != ' ')
			return true;

	return false;
}

void Parser::extractKey(std::string &key, size_t const &sepPos, const std::string &line) const
{
	key = line.substr(0, sepPos);

	if (key.find('\t') != line.npos || key.find(' ') != line.npos)
		key.erase(key.find_first_of("\t "));
}

void Parser::extractValue(std::string &value, size_t const &sepPos, const std::string &line) const
{
	value = line.substr(sepPos + 1);
	value.erase(0, value.find_first_not_of("\t "));
	value.erase(value.find_last_not_of("\t ") + 1);
}

void Parser::extractContents(const std::string &line)
{
	std::string temp = line;

	temp.erase(0, temp.find_first_not_of("\t "));
	size_t sepPos = temp.find('=');

	std::string key, value;
	extractKey(key, sepPos, temp);
	extractValue(value, sepPos, temp);

	if (!keyExists(key))
		contents.insert(std::pair<std::string, std::string>(key, value));
	
}

void Parser::parseLine(const std::string &line, size_t const lineNo)
{
	if (line.find('=') == line.npos)
		return;
	if(!validLine(line))
		return;

	extractContents(line);
}

bool Parser::keyExists(const std::string &key) const
{
	return contents.find(key) != contents.end();
}

std::string Parser::getStringOfKey(const std::string &key) const
{
	if (!keyExists(key))
		return NULL;

	return (contents.find(key)->second);
}

int	Parser::getIntOfKey(const std::string &key) const
{
	if (!keyExists(key))
		return NULL;

	return atoi((contents.find(key)->second.c_str()));
}

bool Parser::getBoolOfKey(const std::string &key) const
{
	if (!keyExists(key))
		return NULL;

	return (BOOL)atoi((contents.find(key)->second.c_str()));
}