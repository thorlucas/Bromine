#ifndef _BROMINE_H_
#define _BROMINE_H_

// #include <SDL2/SDL.h>
#include <unordered_map>

#include <typeinfo>
#include <typeindex>

#include "Scene.h"
#include "Factory/Factory.h"
#include "Server/Server.h"
#include "Trait/Trait.h"

#include <functional>

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
	// std::unordered_map<std::type_index, Factory&> factoryMap;

public:
	// Singleton Setup
	/**
	 * Returns an instance of the Bromine engine singleton.
	 */
	static Bromine& instance() {
		static Bromine instance;
		return instance;
	}

	// template <typename T>
	// static T& instance() {
	// 	static T instance;
	// 	return instance;
	// }

	// template<typename T, typename F>
	// bool registerServer(std::function<T&()>)

	// template<typename T>
	// bool bindServer(std::function<T*()> closure) {
	// 	return serverMap.insert(std::pair<std::type_index, Server*>(typeid(T), closure())).second;
	// }
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

	// template <typename T>
	// bool registerServer(T& server) {
	// 	return serverMap.insert( std::pair<std::type_index, Server&>(typeid(T), server) ).second;
	// }


	// template <typename T>
	// T& getFactory() {
	// 	return dynamic_cast<T&>( factoryMap.at(typeid(T)) );
	// }

	// template <typename T>
	// bool registerFactory(T& factory) {
	// 	return factoryMap.insert( std::pair<std::type_index, Factory&>(typeid(T), factory) ).second;
	// }


	void runWithScene(Scene* rootScene);
};

}

#endif // _BROMINE_H_