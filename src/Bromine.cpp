#include "Bromine.h"

#include "Config/Config.h"
#include "Config/ServersConfig.h"

namespace BromineEngine {

// TODO: Make resource manager have no constructor parameters,
// initialize everything later
Bromine::Bromine() :
	serverClosures(autoloadServerClosures),
	nodeServer(getServer<NodeServer>()),
	renderServer(getServer<RenderServer>()),
	eventServer(getServer<EventServer>()),
	logicServer(getServer<LogicServer>()),
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


	Server* server = serverClosures.at(typeIndex)();
	serverMap.insert(std::pair<std::type_index, Server&>(typeIndex, *server));
	serverVector.push_back(server);

	return *server;
}

bool Bromine::run() {
	return run(makeInitialScene());
}

bool Bromine::run(Scene* rootScene) {
	currentScene = rootScene;

	currentScene->loadScene();

	while (running) {
		for (int i = 0; i < serverVector.size(); ++i) {
			serverVector.at(i)->update();
		}
	}

	return 0;
}

void Bromine::quit() {
	running = false;
}

Node& Bromine::node(NodeID node) {
	return Bromine::instance().nodeServer.getNode(node);
}


} // namespace BromineEngine