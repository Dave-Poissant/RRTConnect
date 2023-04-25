
#include <chrono>
#include <thread>
#include <iostream>

#include <SFML/System/Clock.hpp>

#include "RRTConnect/Application.h"

/*static void capFrameRate(sf::Time* then, sf::Time* remainder, sf::Clock* clock)
{
	sf::Time wait, frameTime;

	wait = sf::milliseconds(16 + remainder->asMilliseconds());
	*remainder -= sf::milliseconds(remainder->asMilliseconds());
	frameTime = sf::milliseconds(clock->getElapsedTime().asMilliseconds()) - sf::milliseconds(then->asMilliseconds());
	wait -= sf::milliseconds(frameTime.asMilliseconds());

	if (wait < sf::milliseconds(1))
	{
		wait = sf::milliseconds(1);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(wait.asMilliseconds()));

	*remainder += sf::milliseconds(0.667);
	*then = sf::milliseconds(clock->getElapsedTime().asMilliseconds());
}*/

static void cleanup()
{
	std::cout << "static void cleanup()" << std::endl;
}

int main()
{
	atexit(cleanup);

	Config config;
    Application* app = new Application(config);
	//SolverRRTConnect* solver = new SolverRRTConnect(app->getGrid(), &config);
	app->playingLoop();
	//std::thread t1(&Application::playingLoop, app);
	//std::thread t2(&SolverRRTConnect::solve, solver);
	
	//t1.join();
	//t2.join();
	
	return 0;
}