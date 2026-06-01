#include <DX3D/Graphics/VertexShaderSignature.h>
#include<DX3D/Graphics/ShaderBinary.h>
#include <d3dcompiler.h>
#include <DX3D/Graphics/GraphicsUtils.h>
#include <ranges>
dx3d::VertexShaderSignature::VertexShaderSignature(const VertexShaderSignatureDesc& desc, const GraphicsResourceDesc& gDesc)
	: GraphicsResource(gDesc), m_vsBinary(desc.vsBinary)

{
	if (!desc.vsBinary) DX3DLogInvalidArgThrow("no shader binary detected");
	if(desc.vsBinary->getType()!=ShaderType::VertexShader)
		DX3DLogInvalidArgThrow("invalid vertex shader binary for 'vsBinary' ");
	
	auto vsData = m_vsBinary->getData(); // get the data from desc
	DX3DGraphicsLogErrorAndThrowOnFail(
		D3DReflect(
			vsData.data,
			vsData.dataSize,
			IID_PPV_ARGS(&m_shaderReflection)
		), "error on executing dx3d reflect");

	D3D11_SHADER_DESC shaderDesc{};

	DX3DGraphicsLogErrorAndThrowOnFail(
		m_shaderReflection->GetDesc(&shaderDesc), "1d3d11shaderReflect::GetDesc failure");


	m_numElements = shaderDesc.InputParameters;
	 
	D3D11_SIGNATURE_PARAMETER_DESC params[D3D11_STANDARD_VERTEX_ELEMENT_COUNT]{};

	for (auto i : std::views::iota(0u, m_numElements))
	{
		DX3DGraphicsLogErrorAndThrowOnFail(
			m_shaderReflection->GetInputParameterDesc(i, &params[i]),
			"ID3D11ShaderReflection::GetInputParameterDesc failure"
		);
	}

	for(auto i: std::views::iota(0u, m_numElements))
	{
		auto param = params[i];
		m_elements[i] =
		{
			param.SemanticName,
			param.SemanticIndex,
			GraphicsUtils::GetDXGIFormatFromMask(param.ComponentType, param.Mask),
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}; 
	}
	
}

dx3d::BinaryData dx3d::VertexShaderSignature::getShaderBinaryData() const noexcept
{
	return m_vsBinary->getData();
}

dx3d::BinaryData dx3d::VertexShaderSignature::getInputElementsData() const noexcept
{
	return
	{
		m_elements,
		m_numElements
	};
}
