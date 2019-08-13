#include "Bromine.h"

#include "Config/Config.h"
#include "Config/ServersConfig.h"

#include "Server/NodeServer.h"
#include "Server/RenderServer.h"

namespace BromineEngine {

// TODO: Make resource manager have no constructor parameters,
// initialize everything later
Bromine::Bromine() :
	serverClosures(autoloadServerClosures),
	nodeServer(getServer<NodeServer>()),
	renderServer(getServer<RenderServer>()),
	logger(Logger::DEBUG) {

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

	Server& server = *serverClosures.at(typeIndex)();
	serverMap.insert(std::pair<std::type_index, Server&>(typeIndex, server));

	return server;
}

bool Bromine::run() {
	return run(makeInitialScene());
}

bool Bromine::run(Scene* rootScene) {
	currentScene = rootScene;

	currentScene->loadScene();

	SDL_Event sdlEvent;

	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
				case SDL_QUIT:
					running = false;
					break;
				default:
					break;
			}
		}

		renderServer.update();
	}

	return 0;
}

Node& Bromine::node(NodeID node) {
	return Bromine::instance().nodeServer.getNode(node);
}


} // namespace BromineEngine