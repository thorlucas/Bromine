#include <Bromine.h>

namespace BromineEngine {

Bromine::Bromine() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL initialization failed: %s\n", SDL_GetError());
		return;
	}

	window = SDL_CreateWindow("Bromine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	if (window == NULL) {
		printf("SDL could not create window: %s\n", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("SDL could not create renderer: %s\n", SDL_GetError());
		return;
	}

	resourceManager = new ResourceManager("resources");

	running = true;
	currentScene = nullptr;
}

Bromine::~Bromine() {
	delete resourceManager;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Bromine::run(Scene* rootScene) {
	currentScene = rootScene;

	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				default:
					break;
			}
		}

		currentScene->update();
	}

	SDL_Quit();
	return 0;
}

SDL_Renderer* Bromine::getRenderer() {
	return renderer;
}

ResourceManager* Bromine::getResourceManager() {
	return resourceManager;
}

} // namespace BromineEngine