#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
namespace dx3d
{
	class GraphicsPipelineState final : public GraphicsResource
	{
	public:
		GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gDesc);

	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs{};
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps{};

		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout{};

		//friedns

		friend class DeviceContext; // allow device context to access private members of graphics pipeline state to set shaders


	};
}


