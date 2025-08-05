#ifndef Logger_H
#define Logger_H

#if _WIN32
#pragma once
#endif

#include <cstdint>
#include <fstream>
#include <stdarg.h>

enum class ELogColor : uint8_t
{
	COLOR_RED=0,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_WHITE,
	COLOR_RESET,
};

constexpr const char* ToColor(ELogColor Color)
{
	switch (Color)
	{
		case ELogColor::COLOR_RED:
		return "\x1B[31m";
		case ELogColor::COLOR_GREEN:
		return "\x1B[32m";
		case ELogColor::COLOR_YELLOW:
		return "\x1B[33m";
		case ELogColor::COLOR_WHITE:
		return "\x1B[37m";
		case ELogColor::COLOR_RESET:
		default:
		return "\x1B[0m";
	}
}

enum class ELogVerbosity : uint8_t
{
	Verbosity_Fatal = 0,
	Verbosity_Error,
	Verbosity_Warning,
	Verbosity_Display,
	Verbosity_Log,			// Print only to the %DT%.log file
};

class Logger
{
public:
	Logger();
	~Logger();

	void Log(const char* Msg, ...);
	void LogWarning(const char* Msg, ...);
	void LogError(const char* Msg, ...);
	void LogCustomColor(const char* Msg, ELogColor Color, ...);

private:
	std::ofstream LogFile;
	bool bFileWriteable{false};

	// Variadic data parser for DRY
	__forceinline void ParseVArgs(char* OutBuffer, size_t BufferSize, const char* Format, va_list& Args)
	{
		va_list TmpArgs;
		va_copy(TmpArgs, Args);
		vsnprintf(OutBuffer, BufferSize, Format, TmpArgs);
		va_end(TmpArgs);
	}
};

extern Logger g_Logger;

#endif //Logger_H