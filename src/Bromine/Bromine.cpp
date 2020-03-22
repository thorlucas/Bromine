#include "Bromine.h"

#include <Config/ServersConfig.h>

namespace BromineEngine {

Bromine::Bromine() :
	serverClosures(autoloadServerClosures),
	nodeServer(getServer<NodeServer>()),
	renderServer(getServer<RenderServer>()),
	eventServer(getServer<EventServer>()),
	logicServer(getServer<LogicServer>()) {

	Logger::instance().setMinimumPriority(LOGGER_MIN_PRIORITY);

	for (auto it : autoInitServers) {
		getServer(it); // ensures servers are constructed
	}

	running = true;
	currentScene = nullptr;
}

Bromine::~Bromine() {
	for (auto& it : serverMap) {
		delete &(it.second);
	}

	SDL_Quit();
}

Server& Bromine::getServer(std::type_index typeIndex) {
	auto ret = serverMap.find(typeIndex);
	if (ret != serverMap.end()) return ret->second;


	Server* server = serverClosures.at(typeIndex)();
	serverMap.insert(std::pair<std::type_index, Server&>(typeIndex, *server));
	serverVector.push_back(server);

	return *server;
}

bool Bromine::run() {
	return run(makeInitialScene());
}

bool Bromine::run(Scene* rootScene) {
	// lastFrame = std::chrono::high_resolution_clock::now();
	// lastSecondFrame = lastFrame;

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
	return Bromine::instance().nodeServer.getNode(node);
}

NodeBuilder Bromine::node() {
	return Bromine::instance().nodeServer.buildNode();
}

Scene* Bromine::getCurrentScene() {
	return currentScene;
}


} // namespace BromineEngine