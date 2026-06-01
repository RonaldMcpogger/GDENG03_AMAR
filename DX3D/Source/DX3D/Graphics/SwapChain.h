#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
namespace dx3d
{
	class SwapChain final : public GraphicsResource
	{
	public:
		  SwapChain(const SwapChainDesc& desc ,const GraphicsResourceDesc& gDesc);
			
		  void present(bool vsync = false); //WOAH VSYNC FROM DA GAMES
		  Rect getSize() const noexcept; // get the size of the swap chain for proper viewport setting during rendering
	private:
		void reloadBuffers();

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{}; 
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv{}; // render target view for the back buffer
		Rect m_size{}; // store the size of the swap chain for proper viewport setting during rendering
		friend class DeviceContext; // allow device context to access private members of swapchain to set render target view

	};
}
