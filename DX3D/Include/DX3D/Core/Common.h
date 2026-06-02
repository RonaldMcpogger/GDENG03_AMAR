#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Math/Rect.h>
namespace dx3d
{
	struct BaseDesc
	{
		Logger& logger;

	};

	struct WindowDesc
	{
		BaseDesc base;
		Rect size{};	
	};

	struct DisplayDesc // display desc needs window
	{
		WindowDesc window;
		GraphicsDevice& graphicsDevice;
	};
	struct GraphicsEngineDesc
	{
		BaseDesc base;
	};
	struct GraphicsDeviceDesc
	{
		BaseDesc base;
	};


	struct SwapChainDesc
	{
		void* minHandle{}; //window handler
		Rect minSize{};
	};
	//shader Enum

	enum class ShaderType
	{
		VertexShader = 0,
		PixelShader
	};

	// new code added:: raster and culltype

	// culling mode types needed for wireframing

	enum class CullType
	{
		Backface = 0, // polygons facing camera 
		Frontface, // polygons facing away from camera
		None
	};

	// Raster Decscription
	struct RasterStateDesc
	{
		bool wireframeState = false;
		CullType cullType{};
	};

	struct ShaderCompileDesc
	{
		const char* shaderSourceName{};
		const void* shaderSourceCode{};
		size_t shaderSourceCodeSize{};
		const char* shaderEntryPoint{};
		ShaderType shaderType{};
	};

	struct VertexShaderSignatureDesc
	{
		const ShaderBinaryPtr& vsBinary;
	};

	struct BinaryData
	{
		const void* data{};
		size_t dataSize{};
	};


	struct GraphicsPipelineStateDesc
	{
		const VertexShaderSignature& vs;
		const	ShaderBinary& ps;
	};

	struct VertexBufferDesc
	{
		const void* vertexList{};
		ui32 vertexListSize{};
		ui32 vertexSize{};
	};


	struct GameDesc
	{
		Rect windowSize{ 1280, 720 };

		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};
}