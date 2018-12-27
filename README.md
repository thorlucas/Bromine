# Bromine: Game Engine
Bromine is lightweight. No need for an editor, no need for learning less powerful scripting languages. You just write C++. That’s it.

## Quick Start
### Compilation
Bromine is a static library. Link it in while compiling your code. Make sure to include the Bromine headers. You’ll also have to include SDL2 and SDL2_image headers and library.
`g++ --std=c++11 -I include -L lib -lBromine -lSDL2 -lSDL2_image main.cpp -o main`

### Nodes and Scenes
In Bromine, everything is a node in a scene. The general pattern for development is to inherit `Scene` and initialize the node tree in the constructor.

```cpp
// HelloWorldScene.h
#include <Bromine.h>
#include <Node/Sprite.h>

using namespace BromineEngine;

class HelloWorldScene : public Scene {
public:
	HelloWorldScene();
};
```

```cpp
// HelloWorldScene.cpp
#include <HelloWorldScene.h>

using namespace BromineEngine;

HelloWorldScene::HelloWorldScene() {
	Sprite* spriteNode = new Sprite("image", "image.jpg");
	root = spriteNode;
}
```
The first parameter in the `Sprite`’s constructor is the resource’s identifier, the second is the path to the resource. We’ll get to the specifics of that later. All you have to know is that `image.jpg` should be in a folder called `resources` in the directory that the executable will be.

After creating the sprite node, we then assign it to `root`. This is the root node for the scene. There can be only one!

### Main Loop
The next step is to create the main loop, and attach this scene to it.

```cpp
// main.cpp
#include <HelloWorldScene.h>

using namespace BromineEngine;

int main(int argc, char const *argv[]) {
	HelloWorldScene* scene = new HelloWorldScene();
	Bromine::Run(scene);

	return 0;
}
```

Build, compile, and you should get something like this:

![Voilà!](https://github.com/thorlucas/Bromine/blob/master/doc/images/screenshot1.png?raw=true)