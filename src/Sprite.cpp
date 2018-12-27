#include <Node/Sprite.h>

namespace BromineEngine {

Sprite::Sprite(std::string resourceIdentifier, std::string filePath) : Renderable(resourceIdentifier, filePath) { }
Sprite::~Sprite() { }

void Sprite::_didEnterScene() {
	// TODO: Do this setup in another function (_didEnterScene) so that people can inherit without messing it up
	Node::_didEnterScene();
	Renderable::_didEnterScene(); // Adds renderable to the queue
	didEnterScene();
}

} // namespace BromineEngine