#ifndef _BROMINE_H_
#define _BROMINE_H_

#include <unordered_map>
#include <vector>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <stdexcept>
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
class Service;

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
	static Bromine* globalInstance;

	bool running; /**< Used to exit out of the main loop. */
	
	/**
	 * This is the current scene that is presented.
	 * Each loop, this scene is updated. 
	 * When added to Bromine, the scene did enter is called.
	 */
	Scene* currentScene;

	std::unordered_map<std::type_index, Server*> serverMap;
	std::vector<Server*> serverVector;

	std::unordered_map<std::type_index, Service*> serviceMap;

public:
	Bromine();

	/**
	 * Returns an instance of the Bromine engine singleton.
	 */
	static Bromine& instance() {
		return *Bromine::globalInstance; // TODO: Does not check for nullptr
	}

	/**
	 * Sets the global instance of Bromine that will be fetched
	 * using Bromine::instance(). This may be changed prior
	 * to any test suites that need mock servers or services.
	 */
	static void setGlobalInstance(Bromine* instance) {
		globalInstance = instance;
	}

	Bromine(Bromine const&) = delete;
	void operator=(Bromine const&) = delete;

	~Bromine();


	// Server registration and fetching
	// Bromine manages owners the server and so should be responsible for creating it. Args are passed in.
	template <typename T, typename ...Ps>
	T& registerServer(Ps... ps) {
		if (serverMap.find(typeid(T)) != serverMap.end()) {
			// TODO: Throw custom error
			throw std::runtime_error("Server already exists");
		}

		T* server = new T(ps...);
		Server* base = dynamic_cast<Server*>(server);

		if (base == nullptr) {
			// TODO: Throw custom error
			throw std::runtime_error("Type passed is not of type server");
		}

		serverVector.push_back(base);
		serverMap.insert(std::pair<std::type_index, Server*>(typeid(T), base));

		return *server;
	}

	template <typename T>
	T& getServer() {
		return *(static_cast<T*>(serverMap.at(typeid(T))));
	}

	template <typename T>
	static T& server() {
		return Bromine::instance().getServer<T>();
	}

	// Service registration
	template <typename T, typename ...Ps>
	T& registerService(Ps... ps) {
		if (serviceMap.find(typeid(T)) != serviceMap.end()) {
			// TODO: Throw custom error
			throw std::runtime_error("Service already exists");
		}

		T* service = new T(ps...);
		Service* base = dynamic_cast<Service*>(service);

		if (base == nullptr) {
			// TODO: Throw custom error
			throw std::runtime_error("Type passed is not of type service");
		}

		serviceMap.insert(std::pair<std::type_index, Service*>(typeid(T), base));

		return *service;
	}

	template <typename T>
	T& getService() {
		return *(static_cast<T*>(serviceMap.at(typeid(T))));
	}

	template <typename T>
	static T& service() {
		return Bromine::instance().getService<T>();
	}

	// Aliases
	
	static Node& node(NodeID node);

	static NodeBuilder node();
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
	
	void quit();

	// Getters and setters

	Scene* getCurrentScene();
};

}

#endif // _BROMINE_H_