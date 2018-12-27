#include <Node/Node.h>

namespace BromineEngine {

Node::Node() { }
Node::~Node() {
	for (auto it: children) {
		if (it != nullptr)
			delete it;
	}
}

void Node::_didEnterScene() {
	for (auto it: children) {
		it->_didEnterScene();
	}
	didEnterScene();
}
void Node::didEnterScene() {}

void Node::_update() {
	for (auto it : children) {
		it->_update();
	}
	update();
}
void Node::update() {}

void Node::addChild(Node* child) {
	// TODO: Check if null
	children.push_back(child);
}

} // namespace BromineEngine