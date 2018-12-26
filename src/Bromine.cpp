#include <Bromine.h>

Bromine::Bromine() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL initialization failed: %s\n", SDL_GetError());
		return;
	}

	window = SDL_CreateWindow("Bromine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	if (window == NULL) {
		printf("SDL could not create window: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

	running = true;
}

int Bromine::run() {
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
	}

	SDL_Quit();
	return 0;
}

