#include <DX3D/Graphics/RasterState.h>

dx3d::RasterState::RasterState(const RasterStateDesc& desc, const GraphicsResourceDesc& gDesc)
	: GraphicsResource(gDesc)
{
	D3D11_RASTERIZER_DESC rasterDesc{};

	rasterDesc.FillMode = desc.wireframeState ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID; // set fill mode based on wireframe state
	//TRUE - WIREFRAME : FALSE - SOLID
	
	switch (desc.cullType)
	{
	case CullType::Backface:
		rasterDesc.CullMode = D3D11_CULL_BACK;
		break;
	case CullType::Frontface:
		rasterDesc.CullMode = D3D11_CULL_FRONT;
		break;
	case CullType::None:
		rasterDesc.CullMode = D3D11_CULL_NONE;
		break;
	default:
		rasterDesc.CullMode = D3D11_CULL_BACK; 
		// reset in case of error
		break;
	}

	//setting raster functions 

	rasterDesc.FrontCounterClockwise = FALSE; // default to clockwise winding order for front faces
	//depth biases for the z buffer so 3d models can be rendered without z fighting. 
	//depth biases are set to 0 since engine is currently using primitive triangles for now
	rasterDesc.DepthBias = 0; 
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	rasterDesc.DepthClipEnable = TRUE; // allows objects to be clipped by depth
	rasterDesc.ScissorEnable = FALSE; // scissor test cannot use it for now due to needing setscissor rects hence false
	rasterDesc.MultisampleEnable = FALSE;
	rasterDesc.AntialiasedLineEnable = FALSE; //ramengine dont have multisample nor AA right now

	m_rasterDesc = rasterDesc; // after setting up description store it here to get passed and called to device context

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rs;
	//creating Rasterstate object
	DX3DGraphicsLogErrorAndThrowOnFail(
		m_device.CreateRasterizerState(&m_rasterDesc, &rs),
		"error in creating rasterizer state"); /// throw error if things go wrong in raster creation
	//pass state here
	m_rState = rs;

}

ID3D11RasterizerState* dx3d::RasterState::getState() const noexcept
{
	return m_rState.Get();
}

 const D3D11_RASTERIZER_DESC& dx3d::RasterState::getDesc() const noexcept
{
	return m_rasterDesc;
}
