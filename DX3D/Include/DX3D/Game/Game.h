#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>
namespace dx3d
{
	class Game : public Base
	{
	public:
	explicit Game(const GameDesc& desc);
		virtual ~Game() override;

		virtual void run() final; //final keyword means run method cannot be overwritten

	private:
		void onInternalUpdate(); // aka the update loop

	private:
		std::unique_ptr<Logger> m_loggerptr{};
		std::unique_ptr<GraphicsEngine> m_graphicsEngine{};
		std::unique_ptr<Display> mon_Display{};
		
		
		bool isRunning{ true };
	};
};

