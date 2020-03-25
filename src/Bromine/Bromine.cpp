#include "Bromine.h"
#include <SDL2/SDL.h>

#include <Bromine/Server/Server.h>
#include <Bromine/Service/Service.h>

#include <Bromine/Server/NodeServer.h>

namespace BromineEngine {

Bromine* Bromine::globalInstance = nullptr;

Bromine::Bromine() {

	Logger::instance().setMinimumPriority(LOGGER_MIN_PRIORITY);
	Logger::instance().logFile(logFileName);

	running = true;
	currentScene = nullptr;
}

Bromine::~Bromine() {
	for (auto& it : serverVector) {
		delete it;
	}

	for (auto& it : serviceMap) {
		delete it.second;
	}

	SDL_Quit();
}

bool Bromine::run(Scene* rootScene) {
	currentScene = rootScene;

	currentScene->loadScene();

	uint32_t thisFrame;
	uint32_t lastFrame = SDL_GetTicks();
	uint32_t delta;
	uint32_t acc = 0;
	uint32_t frameCount = 0;

	while (running) {
		thisFrame = SDL_GetTicks();
		delta = thisFrame - lastFrame;
		acc += delta;

		for (int i = 0; i < serverVector.size(); ++i) {
			serverVector.at(i)->update(static_cast<double>(delta) / 1000.0);
		}

		++frameCount;
		if (acc >= 1000) {
			Bromine::log(Logger::DEBUG, "[FPS] %d", frameCount);
			acc = 0;
			frameCount = 0;
		}


		lastFrame = thisFrame;

		// ++framesInSecond;
		// if (std::chrono::duration_cast<std::chrono::duration<double>>(thisFrame - lastSecondFrame).count() >= 1.0) {
		// 	Bromine::log(Logger::DEBUG, "[FPS] %d", framesInSecond);
		// 	lastSecondFrame = thisFrame;
		// 	framesInSecond = 0;
		// }

		// lastFrame = thisFrame;

		// int delayMs = ((1.0 / 60.0) - delta.count()) * 1000;
		// if (delayMs > 0) {
		// 	SDL_Delay(delayMs);
		// }

		// SDL_Delay(1000);

		// SDL_Delay(static_cast<int>(((1.0 / 60.0) - delta.count()) * 1000));
	}

	return 0;
}

void Bromine::quit() {
	running = false;
}

Node& Bromine::node(NodeID node) {
	return Bromine::server<NodeServer>().getNode(node);
}

NodeBuilder Bromine::node() {
	return Bromine::server<NodeServer>().buildNode();
}

Scene* Bromine::getCurrentScene() {
	return currentScene;
}


} // namespace BromineEngine