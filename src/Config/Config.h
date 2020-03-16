#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Bromine/Scene/Scene.h>
#include <App/Scene/ExampleScene.h>

namespace BromineEngine {

// TODO:
static Scene* makeInitialScene() {
	return new ExampleScene;
}
// static Scene* const initialScene = new ExampleScene;

static const int windowWidth = 1280;
static const int windowHeight = 720;

static const char* resourcePath = "../resources/";

}

#endif // _CONFIG_H_
