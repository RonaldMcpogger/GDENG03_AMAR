#pragma once

// for error logs and info logs necessary for degbugging
namespace dx3d
{
	class Logger final
	{
	public:
		enum class LogLevel
		{
			Error = 0,
			Warning,
			Info
		};

		explicit Logger(LogLevel loglevel = LogLevel::Error);
		~Logger();
		void log(LogLevel logLevel, const char* message);
	protected:
		Logger(const Logger&) = delete; // default copy constructor
		Logger(Logger&&) = delete; // default move constructor
		Logger& operator=(const Logger&) = delete; // default copy assignment operator
		Logger& operator=(Logger&&) = delete; // default move assignment operator
	
		
	private:
		LogLevel m_logLevel = LogLevel::Error;
	};

}

#define DX3DLog(logger,type,message)\
logger.log((type),message)

#define DX3DLogThrow(logger,exception,type,message)\
{\
	DX3DLog(logger,type,message);\
	throw exception(message);\
}

