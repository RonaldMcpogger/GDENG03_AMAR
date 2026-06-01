#include <DX3D/All.h>



int main()
{

	try {
		dx3d::Game game({ {1280,720},dx3d::Logger::LogLevel::Info });
		game.run();
	}
	catch (const std::runtime_error& e)
	{
		return EXIT_FAILURE;
	}
	catch (const std::exception& e)
	{
		return EXIT_FAILURE;
	}
	catch (const std::invalid_argument&)
	{
		return EXIT_FAILURE;
	}
	catch (...) /// catch all other exceptions
	{
		return EXIT_FAILURE;
	}
	



	return EXIT_SUCCESS;
}