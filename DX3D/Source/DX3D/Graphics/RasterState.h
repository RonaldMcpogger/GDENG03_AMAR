#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <d3d11.h>
namespace dx3d
{
	class RasterState final : public GraphicsResource
	{
	public:
		// raster constructor 
		RasterState(const RasterStateDesc& desc, const GraphicsResourceDesc& gDesc);

	public:
		ID3D11RasterizerState* getState() const noexcept;
		const D3D11_RASTERIZER_DESC& getDesc() const noexcept;
	}
	private:
	
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rState{}; // rasterizer state object

		D3D11_RASTERIZER_DESC m_rasterDesc{}; 
		
	};
}
