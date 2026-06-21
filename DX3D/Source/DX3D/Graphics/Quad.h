#pragma once

#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
//

namespace dx3d
{
	class Quad
	{
		public:
			struct Vertex  
			{
				Vec3 position;
				Vec4 color;
			};

		Quad(GraphicsDevice& device, const Vec3& position, const Vec4& color, const Vec3& scale);// constructor
		void setPos(const Vec3& pos);// position move
		void setColor(const Vec4& color);// color set
		void setScale(const Vec3& scale);// scale size
		void setColorCorner(ui32 cornerIndex, const Vec4& color); // color corners

		//draw
		void draw(DeviceContext& context) const; // the draw function from graphics engine

	private:
		void uploadVertexBuffer(); // rebuild vertex data and recreate vertex buffer

	private:

		GraphicsDevice& m_device;
		VertexBufferPtr m_vb{};

		//transform data
		Vec3 m_position{};
		Vec4 m_color{};
		Vec3 m_scale{ .5f,.5f,.5f};
		
		//corners
		Vec4 m_cornerColors[4]{
			Vec4(1.0f, 0.0f, 0.0f, 1.0f), // Bottom-left corner
			Vec4(0.0f, 1.0f, 0.0f, 1.0f), // Bottom-right corner
			Vec4(0.0f, 0.0f, 1.0f, 1.0f), // Top-right corner
			Vec4(1.0f, 1.0f, 0.0f, 1.0f)  // Top-left corner
		};


	};

}