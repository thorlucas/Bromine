#include <Node/Sprite.h>

namespace BromineEngine {

Sprite::Sprite(std::string resourceIdentifier, std::string filePath) : Renderable(resourceIdentifier, filePath) { }
Sprite::~Sprite() { }

void Sprite::preDidEnterScene() {
	Node::preDidEnterScene();
	Renderable::preDidEnterScene(); // Adds renderable to the queue
	didEnterScene();
}

} // namespace BromineEngine