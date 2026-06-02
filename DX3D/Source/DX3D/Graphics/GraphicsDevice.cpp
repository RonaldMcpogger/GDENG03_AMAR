#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/DeviceContext.h>

// note to ram, when making new classes for graphics dont forget to include header here
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/VertexShaderSignature.h>
#include <DX3D/Graphics/RasterState.h>


using namespace dx3d;
dx3d::GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc) : Base(desc.base)
{
	D3D_FEATURE_LEVEL featureLevel{}; // set the feature level to 11.0
	UINT createDeviceFlags = {}; //combine flags
#ifdef DEBUG
	createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG

	DX3DGraphicsLogErrorAndThrowOnFail(D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,createDeviceFlags,NULL,0,D3D11_SDK_VERSION,
		&m_d3dDevice,&featureLevel,&m_d3dDeviceContext), "Failed to create D3D11 device");

	

	//query interface

	DX3DGraphicsLogErrorAndThrowOnFail(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),"QueryInterface failed");
	
	DX3DGraphicsLogErrorAndThrowOnFail(m_dxgiDevice->GetParent(IID_PPV_ARGS( & m_dxgiAdapter)), "GetAdapter failed");
	
	DX3DGraphicsLogErrorAndThrowOnFail(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),"GetParent failed");

	//after passing error make swapchain


} 


dx3d::GraphicsDevice::~GraphicsDevice()
{
}

SwapChainPtr dx3d::GraphicsDevice::createSwapChain(const SwapChainDesc& desc) 
{
	return std::make_shared<SwapChain>(desc,getGraphicsResourceDesc());
}

DeviceContextPtr dx3d::GraphicsDevice::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

ShaderBinaryPtr dx3d::GraphicsDevice::compileShader(const ShaderCompileDesc& desc)
{
	return std::make_shared<ShaderBinary>(desc, getGraphicsResourceDesc());
}

GraphicsPipelineStatePtr dx3d::GraphicsDevice::createGraphicsPipelineState(const GraphicsPipelineStateDesc& desc)
{
	return std::make_shared<GraphicsPipelineState>(desc,getGraphicsResourceDesc());
}

VertexBufferPtr dx3d::GraphicsDevice::createVertexBuffer(const VertexBufferDesc& desc)
{
	return std::make_shared<VertexBuffer>(desc, getGraphicsResourceDesc());
}

VertexShaderSignaturePtr dx3d::GraphicsDevice::createVertexShaderSignature(const VertexShaderSignatureDesc& desc)
{
	return std::make_shared<VertexShaderSignature>(desc, getGraphicsResourceDesc());
}

RasterStatePtr dx3d::GraphicsDevice::createRasterState(const RasterStateDesc& desc)
{
	return std::make_shared<RasterState>(desc, getGraphicsResourceDesc());
}

void dx3d::GraphicsDevice::executeCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};

	DX3DGraphicsLogErrorAndThrowOnFail(context.m_context->FinishCommandList(false, &list)
		, "Error in finishing command list");


	m_d3dDeviceContext->ExecuteCommandList(list.Get(), FALSE);
}

GraphicsResourceDesc dx3d::GraphicsDevice::getGraphicsResourceDesc() const noexcept
{
	return {
		{m_logger},shared_from_this(),*m_d3dDevice.Get(),*m_dxgiFactory.Get()
	
	};
}
