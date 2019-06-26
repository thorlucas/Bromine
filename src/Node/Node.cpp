#include "Node.h"
#include "../Trait/Trait.h"
#include "../Scene/Scene.h"

namespace BromineEngine {

Node::Node(NodeID id) : id(id) {}

Node::~Node() {}

void Node::addChild(NodeID child) {
	children.push_back(child);
}

void Node::activate() {
	Bromine::log(Logger::VERBOSE, "Node %d is activating...", id);
	for (auto it : capabilities) {
		Bromine::instance().getServer(it).activate(id);
	}
}

} // namespace BromineEngine