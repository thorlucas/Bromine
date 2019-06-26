#ifndef _BROMINE_H_
#define _BROMINE_H_

// #include <SDL2/SDL.h>
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>

#include "Scene/Scene.h"
#include "Node/Node.h"
#include "Server/Server.h"
#include "Util/Logger.h"

namespace BromineEngine {

class NodeServer;
class RenderServer;

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

	Server& getServer(std::type_index typeIndex);

	template <typename T>
	T& getServer() {
		return dynamic_cast<T&>(getServer(typeid(T)));
	}


	// Logging stuff
	Logger logger;

	static void log(Logger::Priority priority, const char* fmt,  ...) __attribute__ (( format(printf, 2, 3) )) {
		va_list args;
		va_start(args, fmt);
		Bromine::instance().logger.vlog(priority, fmt, args);
		va_end(args);
	}

	// Server caches
	// Commonly used servers have aliases here for quick access
	NodeServer& nodeServer;
	RenderServer& renderServer;

	bool run(Scene* rootScene);
	bool run();
};

}

#endif // _BROMINE_H_