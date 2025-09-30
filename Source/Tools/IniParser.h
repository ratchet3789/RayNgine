#pragma once

#include <string>
#include <unordered_map>
#include <cerrno>
#include <cstring>

class IniParser
{
public:
	IniParser(const char* FilePath);
	~IniParser() {}
	
	// Overloads
	bool TryParseAs(const std::string& Section, const std::string& Key, int& Value);
	bool TryParseAs(const std::string& Section, const std::string& Key, float& Value);
	bool TryParseAs(const std::string& Section, const std::string& Key, bool& Value);
	bool TryParseAs(const std::string& Section, const std::string& Key, std::string& value);

	template<typename T>
	inline T GetOrDefault(const std::string& Section, const std::string& Key, const T& Fallback)
	{
		static_assert(std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, bool> || std::is_same_v<T, std::string>,
		"IniParser only supports int, float, bool and std::string\n");

		T val;
		return TryParseAs(Section, Key, val) ? val : Fallback;
	}

private:
	// Section > Key/RawValue
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ParsedIniData;

	inline void StripLine(std::string& Line);
	inline bool KeyExists(const std::string& Section, const std::string& Key);
};
extern IniParser g_IniParser;