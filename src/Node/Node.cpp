#include <Node/Node.h>

namespace BromineEngine {

Node::Node() { }
Node::~Node() {
	for (auto it: children) {
		if (it != nullptr)
			delete it;
	}
}

void Node::preDidEnterScene() {
	for (auto it: children) {
		printf("  Children entering scene...\n");
		it->preDidEnterScene();
	}
	didEnterScene();
}
void Node::didEnterScene() {}

void Node::preUpdate() {
	for (auto it : children) {
		it->preUpdate();
	}
	update();
}
void Node::update() {}

void Node::addChild(Node* child) {
	// TODO: Check if null
	children.push_back(child);
}

void Node::preInput(InputEvent& event) {
	input(event);
	if (!event.handled) {
		for (auto it : children) {
			it->preInput(event);
		}
	}
}

void Node::input(InputEvent& event) {}

} // namespace BromineEngine