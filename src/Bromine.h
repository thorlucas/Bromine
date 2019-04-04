#ifndef _BROMINE_H_
#define _BROMINE_H_

// #include <SDL2/SDL.h>
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>

#include "Config/Config.h"
#include "Config/ServersConfig.h"

#include "Scene/Scene.h"
#include "Node/Node.h"
#include "Factory/Factory.h"
#include "Server/Server.h"
#include "Trait/Trait.h"

namespace BromineEngine {

/**
 * This is the engine singleton.
 */
class Bromine {
private:
	Bromine();

	bool running; /**< Used to exit out of the main loop. */
	
	/**
	 * This is the current scene that is presented.
	 * Each loop, this scene is updated. 
	 * When added to Bromine, the scene did enter is called.
	 */
	Scene* currentScene;

	std::unordered_map<std::type_index, std::function<Server*()>> serverClosures;
	std::unordered_map<std::type_index, Server&> serverMap; 

public:
	// Singleton Setup
	/**
	 * Returns an instance of the Bromine engine singleton.
	 */
	static Bromine& instance() {
		static Bromine instance;
		return instance;
	}

	Bromine(Bromine const&) = delete;
	void operator=(Bromine const&) = delete;

	~Bromine();


	template<typename T>
	bool registerServer(std::function<T*()> closure) {
		return serverClosures.insert(
			std::pair<std::type_index, std::function<Server*()>>(typeid(T), closure)
		).second;
	}

	template <typename T>
	T& getServer() {
		auto ret = serverMap.find(typeid(T));
		if (ret != serverMap.end()) return dynamic_cast<T&>(ret->second);

		T& server = *dynamic_cast<T*>(serverClosures.at(typeid(T))());
		serverMap.insert(std::pair<std::type_index, Server&>(typeid(T), server));
		return server;
	}


	bool run(Scene* rootScene);
	bool run();
};

}

#endif // _BROMINE_H_