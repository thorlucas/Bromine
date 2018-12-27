#ifndef _BROMINE_H_
#define _BROMINE_H_

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>

#include <BrUtil.h>
#include <Resource.h>
#include <Scene.h>
#include <Trait/Renderable.h>

namespace BromineEngine {

class Bromine {
private:
	Bromine();

	bool running;

	SDL_Window* window;
	SDL_Renderer* renderer;

	Scene* currentScene;
	ResourceManager* resourceManager;

	std::vector<Renderable*> renderables;

	void render();
public:
	// Singleton Setup
	static Bromine& getInstance() {
		static Bromine instance;
		return instance;
	}

	Bromine(Bromine const&) = delete;
	void operator=(Bromine const&) = delete;

	~Bromine();

	// Aliases
	static int Run(Scene* rootScene) {
		return Bromine::getInstance().run(rootScene);
	}

	static SDL_Renderer* Renderer() {
		return Bromine::getInstance().getRenderer();
	}

	static ResourceManager* Resource() {
		return Bromine::getInstance().getResourceManager();
	}
	
	// Methods
	int run(Scene* rootScene);
	SDL_Renderer* getRenderer();
	ResourceManager* getResourceManager();

	void addRenderable(Renderable* renderable);
};

} // namespace BromineEngine

#endif // _BROMINE_H_