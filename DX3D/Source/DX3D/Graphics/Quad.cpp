#include <DX3D/Graphics/Quad.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/DeviceContext.h>

dx3d::Quad::Quad(GraphicsDevice& device, const Vec3& position, const Vec4& color, const Vec3& scale)
	: m_device(device), m_position(position), m_color(color), m_scale(scale)
{
	for(int  i = 0; i < 4; ++i)
		m_cornerColors[i] = color; // initialize all corners to the same color
	uploadVertexBuffer(); // create vertex buffer with initial data
}

void dx3d::Quad::setPos(const Vec3& pos)
{
	m_position = pos;
	uploadVertexBuffer(); 
}

void dx3d::Quad::setColor(const Vec4& color)
{
	m_color = color;
	uploadVertexBuffer();
}

void dx3d::Quad::setScale(const Vec3& scale)
{
	m_scale = scale;
	uploadVertexBuffer();
}

void dx3d::Quad::setColorCorner(ui32 cornerIndex, const Vec4& color)
{
	if (cornerIndex < 4)
	{
		m_cornerColors[cornerIndex] = color;
		uploadVertexBuffer();
	}
}

void dx3d::Quad::draw(DeviceContext& context) const
{
	if (!m_vb) return; // check if vertex buffer is valid before drawing
	context.setVertexBuffer(*m_vb);
	context.drawTriangleList(m_vb->getVertexListSize(), 0u); // draw 6 vertices to form 2 triangles for the quad
}

void dx3d::Quad::uploadVertexBuffer()
{
	// stuff neeeded for  makinga quad 
	
	const float halfWidth = m_scale.x * 0.5f;
	const float halfHeight = m_scale.y * 0.5f;

	//calculate the  corners in order to get the corners of a quad 

	const Vec3 corners[4] = {
		{ m_position.x - halfWidth, m_position.y - halfHeight, m_position.z }, // Bottom-left - 0
		{ m_position.x + halfWidth, m_position.y - halfHeight, m_position.z }, // Bottom-right - 1
		{ m_position.x + halfWidth, m_position.y + halfHeight, m_position.z }, // Top-right - 2
		{ m_position.x - halfWidth, m_position.y + halfHeight, m_position.z }  // Top-left - 3
	};

	const Vertex vertexList[]
		=
	{
		{ corners[0], m_cornerColors[0] }, // Bottom-left
		{ corners[2], m_cornerColors[2] }, // Bottom-right
		{ corners[1], m_cornerColors[1] }, // Top-right
		
		{ corners[2], m_cornerColors[2] }, // Top-right
		{ corners[0], m_cornerColors[0] }, // Top-left
		{ corners[3], m_cornerColors[3] }  // Bottom-left
	};

	VertexBufferDesc vbDesc{}; //pass the stuff into the bufferdescriptor
	vbDesc.vertexList = vertexList;
	vbDesc.vertexListSize = std::size(vertexList);
	vbDesc.vertexSize = sizeof(Vertex);

	m_vb = m_device.createVertexBuffer(vbDesc); // then create/bind buffers

}
