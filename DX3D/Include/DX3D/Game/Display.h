#pragma once
#include <DX3D/Window/Window.h>
namespace dx3d
{
	class Display final : public Window // class that allows the render of objects to the screen
	{
	public:
	explicit Display(const DisplayDesc& desc);

	SwapChain& getSwapChain()  noexcept; // getter for swapchain to be used in graphics engine render method

	private:
		SwapChainPtr m_swapChain{};
	};
}


