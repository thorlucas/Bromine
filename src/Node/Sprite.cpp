#include <Node/Sprite.h>

namespace BromineEngine {

Sprite::Sprite(std::string resourceIdentifier, std::string filePath) : Renderable(resourceIdentifier, filePath) { }
Sprite::~Sprite() { }

void Sprite::_didEnterScene() {
	Node::_didEnterScene();
	Renderable::_didEnterScene(); // Adds renderable to the queue
	didEnterScene();
}

} // namespace BromineEngine