#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/VertexShaderSignature.h>

#include <fstream>
using namespace dx3d;


dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc) 
	: Base(desc.base)
{

	
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{ m_logger });


	//device

	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();
	//sv target define  ps shader
	
	
	
	constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl"; /// pass the hlsl here
	
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream)DX3DLogErrorThrow("Failed to open shader file");

	std::string shaderFileData{
		std::istreambuf_iterator<char>(shaderStream),
		std::istreambuf_iterator<char>()

	};
	
	//float 4 ps vec is color 
	auto shaderSourceCode = shaderFileData.c_str();

	auto shaderSourceCodeSize = shaderFileData.length();


	auto vs =device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize
		,"VSMain", ShaderType::VertexShader});


	auto ps = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize
		,"PSMain", ShaderType::PixelShader });

	auto vsSig = device.createVertexShaderSignature({ vs });

	m_pipeline = device.createGraphicsPipelineState({ *vsSig,*ps });
	
	//set vertex coordinates here figure out way to get the  vertex data and render it here, 
	
	//the actual vertex point data used for making quads or triangle
	const Vertex vertexList[] = 
	{
		{	{-0.4f, -0.4f, 0.0f},{0,1,0,1}	}, // {x,y,z}, {r,g,b,a}
		{	{-0.4f, 0.4f, 0.0f},{0,1,0,1}	},
		{	{0.4f, 0.4f, 0.0f},{0,1,0,1}	}, 

		{	{0.3f, 0.3f, 0.0f},{0,1,0,1}	}, 
		{	{0.3f, -0.3f, 0.0f},{0,1,1,1}	},
		{	{-0.3f, -0.3f, 0.0f},{0,1,0,1}	}  
	};
	m_vb = device.createVertexBuffer({ vertexList,	std::size(vertexList), sizeof(Vertex) });

}


dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice()  noexcept
{
	return *m_graphicsDevice;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain) // where the render happens
{
	auto& context = *m_deviceContext;
	
	context.clearAndSetBackBuffer(swapChain, {0.27f,0.35f,0.40f,1.f }); // the color screen clear

	//graphics pipeline set state in order to bind shaders to the pipeline
		context.setGraphicsPipelineState(*m_pipeline);

		//set viewport size 
		context.setViewportSize(swapChain.getSize());

	//bind vertex buffer
	 
		auto& vb = *m_vb;
		context.setVertexBuffer(vb);

		//draw call
		context.drawTriangleList(vb.getVertexListSize(), 0u); // first vertice so start vertex is 0

	
	//get device context and execute command list
	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);

	swapChain.present(); // present with vsync enabled to prevent tearing




}
