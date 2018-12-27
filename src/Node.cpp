#include <Node/Node.h>

namespace BromineEngine {

Node::Node() { }
Node::~Node() { }

void Node::didEnterScene() {
	for (auto it: children) {
		it->didEnterScene();
	}
}

void Node::update() {
	for (auto it : children) {
		it->update();
	}
}

void Node::addChild(Node* child) {
	// TODO: Check if null
	children.push_back(child);
}

} // namespace BromineEngine