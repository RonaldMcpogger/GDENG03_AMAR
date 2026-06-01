#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h> // shouldnt this be remove since Core exists?
#include <DX3D/Game/Display.h>

dx3d::Game::Game(const GameDesc& desc)
	: Base({ *std::make_unique<Logger>(desc.logLevel).release() }),
	m_loggerptr(&m_logger)
{
	//m_loggerptr = std::make_unique<Logger>(Logger::LogLevel::Info);

	// declare and instantiate the engine and display monitor
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{ m_logger});
	mon_Display = std::make_unique<Display>(DisplayDesc
		{ {m_logger, desc.windowSize},m_graphicsEngine->getGraphicsDevice() });

	DX3DLogInfo("Game initialized successfully.");
}




dx3d::Game::~Game()
{
	DX3DLogInfo("Game died successfully.");
} 

void dx3d::Game::onInternalUpdate() // the render loop including update 
{
	m_graphicsEngine->render(mon_Display->getSwapChain());

}