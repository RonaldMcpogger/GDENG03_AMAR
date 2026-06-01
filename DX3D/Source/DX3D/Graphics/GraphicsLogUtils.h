#pragma once
#include <DX3D/Core/Logger.h>
#include <d3d11.h>
namespace dx3d
{
	namespace GraphicsLogUtils
	{
		inline void CheckShaderCompile(Logger& logger, HRESULT hr, ID3DBlob* errorBlob)
		{
			auto errorMsg = errorBlob ? 
			static_cast<const char*>(errorBlob->GetBufferPointer()) : nullptr;
			// I am  simplifying this later. 
			if (FAILED(hr))
			{
				if (errorMsg)
				{
					DX3DLogThrow(logger,std::runtime_error,Logger::LogLevel::Error,errorMsg);
				}
				else
				{
					DX3DLogThrow(logger, std::runtime_error, Logger::LogLevel::Error, "ShaderCompile Fail");

				}
			}
			if (errorMsg)
			{
				DX3DLog(logger, Logger::LogLevel::Warning, errorMsg);
			}
		} 

	}

}

#define DX3DGraphicsLogErrorAndThrowOnFail(hr,message) \
	{\
		auto res =(hr);\
		if (FAILED(res))\
		{\
			DX3DLogErrorThrow(message);\
		}\
	}

#define DX3DGraphicsCheckShaderCompile(hr,errorBlob) \
{\
auto res = (hr);\
dx3d::GraphicsLogUtils::CheckShaderCompile(getLogger(), res, errorBlob);\
}