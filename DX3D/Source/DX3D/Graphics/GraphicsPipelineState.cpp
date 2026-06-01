#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <dx3d/Graphics/VertexShaderSignature.h> 

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc,const GraphicsResourceDesc& gDesc)
	:  GraphicsResource(gDesc)
{
	//error handling before pipeline creation

	if (desc.ps.getType() != ShaderType::PixelShader)
		DX3DLogInvalidArgThrow("Invalid pixel shader provided for graphics pipeline state creation");

	auto vs = desc.vs.getShaderBinaryData();
	auto ps = desc.ps.getData();
	auto vsInputElements = desc.vs.getInputElementsData();
	

	DX3DGraphicsLogErrorAndThrowOnFail(
		m_device.CreateInputLayout( 
			static_cast<const D3D11_INPUT_ELEMENT_DESC*>(vsInputElements.data),
			static_cast<ui32>(vsInputElements.dataSize),
			vs.data,
			vs.dataSize,
			&m_layout),
		"error in creating input layout"
	);


	DX3DGraphicsLogErrorAndThrowOnFail(
		m_device.CreateVertexShader(vs.data,vs.dataSize,nullptr,&m_vs),
		"Create vertex shader failed"
	)

		DX3DGraphicsLogErrorAndThrowOnFail(
			m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
			"Create Pixel shader failed"
		);
}
