#ifndef _BROMINE_H_
#define _BROMINE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>

#include <Scene.h>

namespace BromineEngine {

class Bromine {
private:
	Bromine();

	bool running;
	SDL_Window* window;

	Scene* currentScene;
public:
	// Singleton Setup
	static Bromine& getInstance() {
		static Bromine instance;
		return instance;
	}

	Bromine(Bromine const&) = delete;
	void operator=(Bromine const&) = delete;

	// Aliases
	static int Run(Scene* rootScene) {
		return Bromine::getInstance().run(rootScene);
	}
	
	// Methods
	int run(Scene* rootScene);
};

} // namespace BromineEngine

#endif // _BROMINE_H_