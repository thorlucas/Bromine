#ifndef _BROMINE_H_
#define _BROMINE_H_

#include <unordered_map>
#include <vector>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <chrono>

#include "Util/Logger.h"
#include "Util/Vec.h"
#include "Util/Typedefs.h"
#include "Util/Errors.h"

namespace BromineEngine {

// Forward declarations
class Scene;
class Node;

class Server;
class NodeServer;
class RenderServer;
class EventServer;
class LogicServer;

class NodeBuilder;

/**
 * This is the engine singleton.
 * 
 * It's main purpose is to handle the various servers, by
 * calling them in the main loop, and allowing the 
 * registration and fetching thereof.
 *
 * It also manages the loading and unloading of scenes. TODO: Why?
 *
 * Bromine also provides aliases to commonly-used functions.
 *
 * TODO: Why do servers need to be added runtime?
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
	std::vector<Server*> serverVector;

	// std::chrono::high_resolution_clock::time_point lastSecondFrame;
	// std::chrono::high_resolution_clock::time_point lastFrame;
	// std::chrono::high_resolution_clock::time_point thisFrame;
	// std::chrono::duration<double> delta;

	// unsigned int framesInSecond;

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


	// Server registration and fetching

	template <typename T>
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

	// Aliases
	
	static Node& node(NodeID node);

	static NodeBuilder node();

	template <typename T>
	static T& server() {
		return Bromine::instance().getServer<T>();
	} 

	// Server aliases
	// Commonly used servers have aliases here for quick access
	
	NodeServer& 	nodeServer;
	RenderServer& 	renderServer;
	EventServer& 	eventServer;
	LogicServer& 	logicServer;


	// Logging

	// TODO: Make a v version that takes a v list 
	static void log(Logger::Priority priority, const char* fmt,  ...) __attribute__ (( format(printf, 2, 3) )) {
		va_list args;
		va_start(args, fmt);
		Logger::instance().vlog(priority, fmt, args);
		va_end(args);
	}


	// Run and quit

	bool run(Scene* rootScene);
	bool run();

	void quit();

	// Getters and setters

	Scene* getCurrentScene();
};

}

#endif // _BROMINE_H_