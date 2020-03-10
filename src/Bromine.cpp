#include "Bromine.h"

#include "Config/ServersConfig.h"

namespace BromineEngine {

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
	lastFrame = std::chrono::high_resolution_clock::now();
	lastSecondFrame = lastFrame;

	currentScene = rootScene;

	currentScene->loadScene();

	while (running) {
		thisFrame = std::chrono::high_resolution_clock::now();
		delta = std::chrono::duration_cast<std::chrono::duration<double>>(thisFrame - lastFrame);

		for (int i = 0; i < serverVector.size(); ++i) {
			serverVector.at(i)->update(delta.count());
		}

		++framesInSecond;
		if (std::chrono::duration_cast<std::chrono::duration<double>>(thisFrame - lastSecondFrame).count() >= 1.0) {
			Bromine::log(Logger::DEBUG, "[FPS] %d", framesInSecond);
			lastSecondFrame = thisFrame;
			framesInSecond = 0;
		}

		lastFrame = thisFrame;
	}

	return 0;
}

void Bromine::quit() {
	running = false;
}

Node& Bromine::node(NodeID node) {
	return Bromine::instance().nodeServer.getNode(node);
}

// NodeBuilder<Node>* Bromine::node() {
// 	return Bromine::instance().nodeServer.buildNode();
// }


} // namespace BromineEngine