#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "../Scene/Scene.h"
#include "../Scene/ExampleScene.h"

namespace BromineEngine {

static Scene* const initialScene = new ExampleScene;

static const int windowWidth = 1280;
static const int windowHeight = 720;

}

#endif // _CONFIG_H_
