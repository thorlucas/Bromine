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

/**
 * This is the engine singleton.
 */
class Bromine {
private:
	Bromine();

	bool running; /**< Used to exit out of the main loop. */

	SDL_Window* window; /**< The main SDL window. */
	SDL_Renderer* renderer; /**< The main renderer. */

	/**
	 * This is the current scene that is presented.
	 * Each loop, this scene is updated. 
	 * When added to Bromine, the scene did enter is called.
	 */
	Scene* currentScene;
	ResourceManager* resourceManager; /**< Manages texture and audio files. */

	/**
	 * A list of Nodes with the Renderable trait.
	 * Each loop, this is rendered front to back.
	 */
	std::vector<Renderable*> renderables;

	void render(); /**< Called each loop to render the renderables. */
public:
	// Singleton Setup
	/**
	 * Returns an instance of the Bromine engine singleton.
	 */
	static Bromine& getInstance() {
		static Bromine instance;
		return instance;
	}

	Bromine(Bromine const&) = delete;
	void operator=(Bromine const&) = delete;

	~Bromine();

	// Aliases
	/**
	 * An alias to run(Scene*).
	 */
	static int Run(Scene* rootScene) {
		return Bromine::getInstance().run(rootScene);
	}

	/**
	 * An alias to getRenderer().
	 */
	static SDL_Renderer* Renderer() {
		return Bromine::getInstance().getRenderer();
	}

	/**
	 * An alias to getResourceManager().
	 */
	static ResourceManager* Resource() {
		return Bromine::getInstance().getResourceManager();
	}
	
	// Methods
	/**
	 * Runs the main loop with a root scene.
	 * The root scene will be updated each frame,
	 * and Scene::didPresent() will be called when added.
	 *
	 * @param rootScene is the root scene.
	 */
	int run(Scene* rootScene);

	/**
	 * @todo Dont expose this!
	 * @returns the main SDL_Renderer*.
	 */
	SDL_Renderer* getRenderer();

	/**
	 * @returns the main ResourceManager.
	 */
	ResourceManager* getResourceManager();

	/**
	 * Adds a Node with the trait Renderable to the
	 * rendering queue. They will be rendered in order
	 * from first (back) to last (front).
	 * 
	 * @param renderable is a pointer to the Node with the Renderable trait.
	 */
	void addRenderable(Renderable* renderable);
};

} // namespace BromineEngine

#endif // _BROMINE_H_