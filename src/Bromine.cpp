#include <Bromine.h>

namespace BromineEngine {

// TODO: Make resource manager have no constructor parameters,
// initialize everything later
Bromine::Bromine() {
	_logManager.log("Initializing Bromine...\n");
	_logManager.log(" Initializing SDL\n");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		_logManager.error("SDL initialization failed: %s\n", SDL_GetError());
		return;
	}

	_logManager.log(" Creating window\n");
	window = SDL_CreateWindow("Bromine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	if (window == NULL) {
		_logManager.error("SDL could not create window: %s\n", SDL_GetError());
		return;
	}

	_logManager.log(" Creating renderer\n");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		_logManager.error("SDL could not create renderer: %s\n", SDL_GetError());
		return;
	}

	_logManager.log(" Initializing resource manager...\n");
	_resourceManager.init("resources");

	_logManager.log(" Allocating memory...\n");
	_allocator.init(0x100000);

	running = true;
	currentScene = nullptr;
}

Bromine::~Bromine() {
	_logManager.log("Destroying Bromine...\n");
	_logManager.log(" Destroying renderer\n");
	SDL_DestroyRenderer(renderer);
	_logManager.log(" Destroying window\n");
	SDL_DestroyWindow(window);
	_logManager.log(" Quitting SDL\n");
	SDL_Quit();
}

int Bromine::runWithScene(Scene* rootScene) {
	_logManager.log("Running Bromine...\n");
	currentScene = rootScene;

	_logManager.log(" Presenting root scene\n");
	rootScene->preDidPresent();

	_logManager.log(" Making event types\n");
	SDL_Event sdlEvent;
	InputEvent event;

	_logManager.log(" Beginning main loop\n");
	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
				case SDL_QUIT:
					running = false;
					break;
				default:
					if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
						event = sdlEvent;
						currentScene->preInput(event);
					}
					break;
			}
		}

		currentScene->preUpdate();
		render();
	}

	return 0;
}

void Bromine::render() {
	SDL_RenderClear(renderer);
	for (auto it : renderables) {
		SDL_RenderCopy(renderer, it->getTexture(), &it->getSrcRect(), &it->getDstRect());
	}
	SDL_RenderPresent(renderer);
}

SDL_Renderer* Bromine::getRenderer() {
	return renderer;
}

ResourceManager& Bromine::getResourceManager() {
	return _resourceManager;
}

LogManager& Bromine::getLogManager() {
	return _logManager;
}

BromineAllocator& Bromine::getAllocator() {
	return _allocator;
}

void Bromine::addRenderable(Renderable* renderable) {
	renderables.push_back(renderable);
}

} // namespace BromineEngine