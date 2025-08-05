#include "Logger.h"
#include <chrono>

Logger::Logger()
{
	time_t SystemTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm CTime = *localtime(&SystemTime);
	std::string LogFileUrl = std::format("{}-{}-{}_{}-{}.log", CTime.tm_year, CTime.tm_mon, CTime.tm_mday, CTime.tm_hour, CTime.tm_min);

	LogFile.open(LogFileUrl, std::ofstream::out);
	if (LogFile.fail())
	{
		g_Logger.LogError("Failed to create LogFile %s. Reason: %s", LogFileUrl, strerror(errno));
		return;
	}
	bFileWriteable = true;
}

Logger::~Logger()
{
	bFileWriteable=false;
	LogFile.close();
}

void Logger::Log(const char* Msg, ...)
{
	char Buffer[1024];

	va_list Args; va_start(Args, Msg);
	ParseVArgs(Buffer, 1024, Msg, Args);
	va_end(Args);

	printf("%s%s%s", ToColor(ELogColor::COLOR_WHITE), Buffer, ToColor(ELogColor::COLOR_RESET));
}

void Logger::LogWarning(const char* Msg, ...)
{
	char Buffer[1024];

	va_list Args; va_start(Args, Msg);
	ParseVArgs(Buffer, 1024, Msg, Args);
	va_end(Args);
	
	printf("%s%s%s", ToColor(ELogColor::COLOR_YELLOW), Buffer, ToColor(ELogColor::COLOR_RESET));
}

void Logger::LogError(const char* Msg, ...)
{
	char Buffer[1024];

	va_list Args; va_start(Args, Msg);
	ParseVArgs(Buffer, 1024, Msg, Args);
	va_end(Args);

	printf("%s%s%s", ToColor(ELogColor::COLOR_RED), Buffer, ToColor(ELogColor::COLOR_RESET));
}

void Logger::LogCustomColor(const char* Msg, ELogColor Color, ...)
{
	char Buffer[1024];

	va_list Args; va_start(Args, Msg);
	ParseVArgs(Buffer, 1024, Msg, Args);
	va_end(Args);

	printf("%s%s%s", ToColor(Color), Buffer, ToColor(ELogColor::COLOR_RESET));
}

Logger g_Logger;
