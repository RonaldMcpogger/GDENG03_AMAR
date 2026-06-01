#include <DX3D/Graphics/SwapChain.h>

dx3d::SwapChain::SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc):
GraphicsResource(gDesc), m_size(desc.minSize)
{

	if (!desc.minHandle) DX3DLogInvalidArgThrow("Invalid window handle provided for swap chain creation");
	
	DXGI_SWAP_CHAIN_DESC dxgiDesc{};

	dxgiDesc.BufferDesc.Width =  std::max(1, desc.minSize.width);
	dxgiDesc.BufferDesc.Height = std::max(1, desc.minSize.height);
	dxgiDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32 bit color format
	dxgiDesc.BufferCount = 2; // double buffering define back buffers why 2? we dont know
	dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // how the swapchain will be used

	dxgiDesc.OutputWindow = static_cast<HWND>(desc.minHandle); // window handle
	dxgiDesc.SampleDesc.Count = 1; // no multisampling or AAliasng
	dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // discard back buffer after presenting
	dxgiDesc.Windowed = TRUE; // start in windowed mode


	DX3DGraphicsLogErrorAndThrowOnFail(m_factory.CreateSwapChain(&m_device, &dxgiDesc, &m_swapChain),
		"An error occurred while creating the swap chain");

	reloadBuffers(); // create render target view for the back buffer
}

void dx3d::SwapChain::present(bool vsync)
{
	DX3DGraphicsLogErrorAndThrowOnFail(m_swapChain->Present(vsync, 0)
	, "error in running Present");

}

dx3d::Rect dx3d::SwapChain::getSize() const noexcept
{
	return m_size;
}

void dx3d::SwapChain::reloadBuffers()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> buffer{};
	
	DX3DGraphicsLogErrorAndThrowOnFail
	(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer)) ,
		"error occured in getting swapchain buffer");

	DX3DGraphicsLogErrorAndThrowOnFail
	(m_device.CreateRenderTargetView(buffer.Get(), nullptr, &m_rtv),
		"error occured in rendering target view");


	

}


 