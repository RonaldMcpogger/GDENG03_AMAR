#include <DX3D/Graphics/VertexBuffer.h>

dx3d::VertexBuffer::VertexBuffer(const VertexBufferDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc), m_vertexSize(desc.vertexSize), m_vertexListSize(desc.vertexListSize)
{
	// error handling

	if(!desc.vertexList)
		DX3DLogInvalidArgThrow("vertex list cannot be null");
	if (!desc.vertexListSize)
		DX3DLogInvalidArgThrow("vertex list size cannot be null");
	if (!desc.vertexSize)
		DX3DLogInvalidArgThrow("vertex size cannot be null");



	D3D11_BUFFER_DESC buffDesc {};
	buffDesc.ByteWidth = desc.vertexListSize * desc.vertexSize;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = desc.vertexList;


	DX3DGraphicsLogErrorAndThrowOnFail(
		m_device.CreateBuffer(&buffDesc, &initData, &m_buffer),
		"error in creating buffer");
	
}

dx3d:: ui32 dx3d::VertexBuffer::getVertexListSize() const noexcept
{
	return m_vertexListSize;
}
