#include <DX3D/Core/Logger.h>
#include <iostream>
dx3d::Logger::Logger(LogLevel loglevel): m_logLevel(loglevel)
{
	std::clog << "RamEngine" << std::endl;

}

dx3d::Logger::~Logger()
{
}

void dx3d::Logger::log(LogLevel logLevel, const char* message) 
{
	auto logLevelToString = [](LogLevel logLevel) -> const char*
	{
		switch (logLevel)
		{
		case LogLevel::Error:
			return "Error";
		case LogLevel::Warning:
			return "Warning";
		case LogLevel::Info:
			return "Info";
		default:
			return "Unknown";
		}
		};
	if(logLevel > m_logLevel)
	{
		return; // if the log level is higher than the current log level, do not log the message
	}
	std::clog << "[DX3D]: " << logLevelToString(logLevel) << ": " << message << std::endl;
}
