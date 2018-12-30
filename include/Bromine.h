#ifndef _BROMINE_H_
#define _BROMINE_H_

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>

#include <BrUtil.h>
#include <Event.h>
#include <Resource.h>
#include <Log.h>
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

	ResourceManager _resourceManager; /**< Manages texture and audio files. */
	LogManager _logManager; /**< Manages logging. */

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
	static Bromine& instance() {
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
	inline static int run(Scene* rootScene) {
		return Bromine::instance().runWithScene(rootScene);
	}

	/**
	 * An alias to getResourceManager().
	 */
	inline static ResourceManager& resourceManager() {
		return Bromine::instance().getResourceManager();
	}

	inline static LogManager& logManager() {
		return Bromine::instance().getLogManager();
	}
	
	// Methods
	/**
	 * Runs the main loop with a root scene.
	 * The root scene will be updated each frame,
	 * and Scene::didPresent() will be called when added.
	 *
	 * @param rootScene is the root scene.
	 */
	int runWithScene(Scene* rootScene);

	SDL_Renderer* getRenderer();

	/**
	 * @returns the main ResourceManager.
	 */
	ResourceManager& getResourceManager();

	LogManager& getLogManager();

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