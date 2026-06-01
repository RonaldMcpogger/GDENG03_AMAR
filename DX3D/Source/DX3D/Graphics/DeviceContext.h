#pragma once
#include<DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Math/Vec4.h>

namespace dx3d
{
	class DeviceContext final : public GraphicsResource
	{
	public:
		explicit DeviceContext(const GraphicsResourceDesc& gDesc);
		void clearAndSetBackBuffer(const SwapChain& swapChain,
			const Vec4& color);
		void setGraphicsPipelineState(const GraphicsPipelineState& pipelineState);
		void setVertexBuffer(const VertexBuffer& buffer);

		void setViewportSize(const Rect& size); // set viewport size for rendering, this is important for proper aspect ratio and rendering to the correct area of the render target
		void drawTriangleList(ui32 vertexCount, ui32 startVertex); // draw call for triangle list topology, this is the most common topology for rendering 3D models
	
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};
		friend class GraphicsDevice; // allow graphics device to access private members of device context to execute command list
	};
}


