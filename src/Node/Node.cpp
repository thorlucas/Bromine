#include "Node.h"
#include "../Trait/Trait.h"
#include "../Scene/Scene.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {


Node::Node(NodeID id) : id(id) {}


Node::~Node() {
	// Deregister?
}

void Node::setParent(NodeID parent) {
	this->parent = parent;
	// TODO: If this already has a parent, tell the parent to remove this child
}

void Node::addChild(NodeID child) {
	children.insert(child);
	Node& nref = Bromine::node(child);
	nref.setParent(id);

	// for (auto& capability : capabilities) {
	// 	Bromine::instance().getServer(capability).nodeAddedChild(id, child);
	// }

	Bromine::log(Logger::DEBUG, "Node %d added child node %d", id, child);
	// TODO: Notify scene
}

void Node::addChild(Node& child) {
	addChild(child.id);
}

void Node::activate() {
	Bromine::log(Logger::DEBUG, "Node %d is activating...", id);

	for (auto& trait : traits) {
		trait->activate();
	}
	
	for (auto it : children) {
		Bromine::node(it).activate();
	}
}

// bool Node::hasCapability(std::type_index capability) {
// 	return capabilities.find(capability) != capabilities.end();
// }

Vec2d& Node::position() {
	return _position;
}

Vec2d Node::position() const {
	return _position;
}

} // namespace BromineEngine