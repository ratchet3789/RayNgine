#include "IniParser.h"
#include <fstream>
#include <stdio.h>
#include <algorithm>

#include "../Debugging/Logger.h"

IniParser::IniParser(const char* FilePath)
{
	std::ifstream IniFileStream(FilePath);
	
	if (IniFileStream.fail())
	{
		// ReSharper disable once CppDeprecatedEntity
		g_Logger.LogError("Failed to load %s.\nReason: \n", FilePath, strerror(errno));
		return;
	}

	std::string Line;
	std::string Category = "Global";
	uint16_t LineNum=0;
	bool bHeaderMalformed=false;
	while (std::getline(IniFileStream, Line))
	{
		LineNum++;
	
		std::erase(Line, ' ');
		std::erase(Line, '\t');
		StripLine(Line);

		// Comments
		if (Line.starts_with('#') || Line.starts_with(';') || Line.starts_with('=') || Line.empty())
		{
			continue;
		}

		// Sections
		if (Line.starts_with("[") )
		{
			if (!Line.ends_with("]"))
			{
				g_Logger.LogError("Invalid format for line %i\n", LineNum);
				bHeaderMalformed=true;
				continue;
			}

			bHeaderMalformed=false;

			Category = Line;
			Category.erase(0,1);
			Category.erase(Category.length() - 1, 1);
			if (ParsedIniData.contains(Category))
			{
				g_Logger.LogWarning("Attempting to create an already existing section %s on line %i.\nThis will be ignored but its data parsed into the original.\n", Line.c_str(), LineNum);
				continue;
			}
			std::unordered_map<std::string, std::string> NewData;
			ParsedIniData.emplace(Category, NewData);
			g_Logger.Log("Parsed Section %s\n", Category.c_str());
			continue;
		}

		if (bHeaderMalformed)
		{
			g_Logger.LogWarning("Section above line %i is malformed. Ignoring data.\n", LineNum);
			continue;
		}

		// Keys
		size_t EqualPos = Line.find("=");
		if (EqualPos != std::string::npos)
		{
			std::string Key,Val;
			Key = Line.substr(0,EqualPos);
			Val = Line.substr(EqualPos+1);

			if(Key.length() == 0 || Val.length() == 0)
			{
				g_Logger.LogWarning("Either Key or Val are invalid on line %i. Ignoring.\n", LineNum);
				continue;
			}

			if (ParsedIniData[Category].contains(Key))
			{
				g_Logger.LogWarning("Attempting to add an already existing variable %s on line %i.\nThis will be ignored.\n", Line.c_str(), LineNum);
				continue;
			}

			ParsedIniData[Category].emplace(Key, Val);
			g_Logger.Log("Parsed Key %s, %s\n", Key.c_str(), Val.c_str());
			continue;
		}
		else
		{
			g_Logger.LogError("Invalid format for line %i\n", LineNum);
			continue;
		}
	}
}

bool IniParser::TryParseAs(const std::string& Section, const std::string& Key, int& Value)
{
	if(!KeyExists(Section, Key))
		return false;

	try
	{
		Value = std::stoi(ParsedIniData[Section][Key]);
	}
	catch (const std::invalid_argument&) {
		g_Logger.LogError("Tried to parse non-number. %s\n", ParsedIniData[Section][Key].c_str());
		Value = 0;
		return false;
	}
	catch (const std::out_of_range&) {
		// number was too big or small
		g_Logger.LogError("Number %s was out of range for type.\n", ParsedIniData[Section][Key].c_str());
		return false;
	}
	return true;
}

bool IniParser::TryParseAs(const std::string& Section, const std::string& Key, float& Value)
{
	if (!KeyExists(Section, Key))
		return false;

	try
	{
		Value = std::stof(ParsedIniData[Section][Key]);
	}
	catch (const std::invalid_argument&) {
		g_Logger.LogError("Tried to parse non-number. %s\n", ParsedIniData[Section][Key].c_str());
		Value = 0;
		return false;
	}
	catch (const std::out_of_range&) {
		// number was too big or small
		g_Logger.LogError("Number %s was out of range for type.\n", ParsedIniData[Section][Key].c_str());
		return false;
	}
	return true;
}

bool IniParser::TryParseAs(const std::string& Section, const std::string& Key, bool& Value)
{
	if (!KeyExists(Section, Key))
		return false;

	Value = false;

	std::string Lower;
	std::transform(Key.begin(), Key.end(), std::back_inserter(Lower), ::tolower);

	if(Lower == "true" || Lower == "1")
		Value = true;
	if (Lower == "false" || Lower == "0")
		Value = false;

	g_Logger.LogError("Expected boolean %s was invalid. Defaulting to FALSE.\n", ParsedIniData[Section][Key].c_str());
	return Value;
}

bool IniParser::TryParseAs(const std::string& Section, const std::string& Key, std::string& Value)
{
	if (!KeyExists(Section, Key))
		return false;

	Value = ParsedIniData[Section][Key];
	return true;
}

inline void IniParser::StripLine(std::string& Line)
{
	size_t SCPosition = Line.find(";");
	size_t HashPosition = Line.find("#");
	size_t CommentPosition = std::min(SCPosition, HashPosition);

	if (CommentPosition != std::string::npos)
	{
		Line.erase(CommentPosition);
	}
}

inline bool IniParser::KeyExists(const std::string& Section, const std::string& Key)
{
	auto SectionItr = ParsedIniData.find(Section);
	if(SectionItr == ParsedIniData.end())
		return false;

	return SectionItr->second.contains(Key);
}

IniParser g_IniParser("Fuck.ini");