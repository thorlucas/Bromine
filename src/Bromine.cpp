#include "Bromine.h"

namespace BromineEngine {

// TODO: Make resource manager have no constructor parameters,
// initialize everything later
Bromine::Bromine() {
	// if (SDL_Init(RenderServer::SDLInitFlags) < 0) {
	// 	return;
	// }

	// RenderServer::instance().init("resources/");

	running = true;
	// currentScene = nullptr;
}

Bromine::~Bromine() {
	// SDL_Quit();
}

// int Bromine::runWithScene(Scene* rootScene) {
// 	currentScene = rootScene;

// 	SDL_Event sdlEvent;
// 	InputEvent event;

// 	while (running) {
// 		while (SDL_PollEvent(&sdlEvent)) {
// 			switch (sdlEvent.type) {
// 				case SDL_QUIT:
// 					running = false;
// 					break;
// 				default:
// 					// SDLSetEventFilter
// 					if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
// 						event = sdlEvent;
// 					}
// 					break;
// 			}
// 		}
// 	}

// 	return 0;
// }


void Bromine::runWithScene(Scene* rootScene) {
	currentScene = rootScene;

	currentScene->loadScene();

	while (running) {
		// RenderServer::instance().render();
	}
}


} // namespace BromineEngine