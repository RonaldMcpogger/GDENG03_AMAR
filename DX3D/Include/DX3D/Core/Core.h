#pragma once
#include <stdexcept>
#include <memory>
// forward declare to avoid circular dependencies and reduce compile time
namespace dx3d
{
	class Base;
	class Window;
	class Game;
	class GraphicsEngine;
	class GraphicsDevice;
	class Logger;

	class SwapChain;
	class Display;
	class DeviceContext;
	class ShaderBinary;

	class GraphicsPipelineState;
	class VertexBuffer;

	class VertexShaderSignature;


	using i32 = int; //32 bits
	using ui32 = unsigned int; //32 bits unsigned
	using f32 = float; //32 bits float
	using f64 = double; //64 bits float

	using SwapChainPtr = std::shared_ptr<SwapChain>; //shared ptr for swapchain since it will be shared between render system and graphics engine
	using DeviceContextPtr = std::shared_ptr<DeviceContext>; //shared ptr for device context since it will be shared between render system and graphics engine
	using ShaderBinaryPtr = std::shared_ptr<ShaderBinary>;
	using GraphicsPipelineStatePtr = std::shared_ptr<GraphicsPipelineState>;
	using VertexBufferPtr = std::shared_ptr<VertexBuffer>;
	using VertexShaderSignaturePtr = std::shared_ptr<VertexShaderSignature>;

}

