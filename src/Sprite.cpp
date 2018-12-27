#include <Node/Sprite.h>

namespace BromineEngine {

Sprite::Sprite(std::string resourceIdentifier, std::string filePath) : Renderable(resourceIdentifier, filePath) { }
Sprite::~Sprite() { }

void Sprite::didEnterScene() {
	Node::didEnterScene();
	Renderable::didEnterScene(); // Adds renderable to the queue
}

} // namespace BromineEngine