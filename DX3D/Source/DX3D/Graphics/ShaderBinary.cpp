#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsUtils.h>
#include <d3dcompiler.h>


dx3d::ShaderBinary::ShaderBinary(const ShaderCompileDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc), m_type(desc.shaderType)
{
	if(!desc.shaderSourceName)
	{
		DX3DLogInvalidArgThrow("no shader source");
	}
	if (!desc.shaderSourceCode)
	{
		DX3DLogInvalidArgThrow("no shader code");
	}
	if (!desc.shaderSourceCodeSize)
	{
		DX3DLogInvalidArgThrow("no shader source code size");
	}
	if (!desc.shaderEntryPoint)
	{
		DX3DLogInvalidArgThrow("no shader entry point");
	}

	//flex
	UINT compileFlags{};

#ifdef _DEBUG
	compileFlags |= D3DCOMPILE_DEBUG;
#endif

	//blob
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob{};

	//compiler
	DX3DGraphicsCheckShaderCompile(


		D3DCompile
		(
			desc.shaderSourceCode,
			desc.shaderSourceCodeSize,
			desc.shaderSourceName,
			nullptr,
			nullptr,
			desc.shaderEntryPoint,
			dx3d::GraphicsUtils::GetShaderModelTarget(desc.shaderType),
			compileFlags,
			0,
			&m_blob,
			&errorBlob
		),
	errorBlob.Get());


}

dx3d::BinaryData dx3d::ShaderBinary::getData() const noexcept
{
	return
	{
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize()
	};
}

dx3d::ShaderType dx3d::ShaderBinary::getType() const noexcept
{
	return m_type;
}
