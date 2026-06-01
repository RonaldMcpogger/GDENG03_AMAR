#pragma once

#include <DX3D/Core/Common.h>

namespace dx3d
{
	class Base
	{
	public:
		explicit Base(const BaseDesc& desc);
		virtual Logger& getLogger()  noexcept final; // add const only when preventing users from modifying engine
		virtual ~Base();
	protected:
		Base(const Base&) = delete; // default copy constructor
		Base(Base&&) = delete; // default move constructor
		Base& operator=(const Base&) = delete; // default copy assignment operator
		Base& operator=(Base&&) = delete; // default move assignment operator

	protected:
		Logger& m_logger; 
	};
}
#define DX3DLogWarning(message)\
	DX3DLog(getLogger(),Logger::LogLevel::Warning,message)

#define DX3DLogInfo(message)\
	DX3DLog(getLogger(),Logger::LogLevel::Info,message)

#define DX3DLogError(message)\
	DX3DLog(getLogger(),Logger::LogLevel::Error,message)

#define DX3DLogErrorThrow(message)\
DX3DLogThrow(getLogger(),std::runtime_error,Logger::LogLevel::Error, message)

#define DX3DLogInvalidArgThrow(message)\
DX3DLogThrow(getLogger(),std::invalid_argument,Logger::LogLevel::Error, message)