#include "Node.h"
#include "../Trait/Trait.h"
#include "../Scene/Scene.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {


Node::Node(NodeID id) : id(id), active(false) {}


Node::~Node() {
	// Deregister?
}

void Node::setParent(NodeID parent) {
	this->parent = parent;
	// TODO: If this already has a parent, tell the parent to remove this child
}

void Node::addChild(NodeID child) {
	children.push_back(child);
	Node& nref = Bromine::node(child);
	nref.setParent(id);

	Bromine::log(Logger::DEBUG, "Node %d added child node %d", id, child);
	// TODO: Notify scene
}

void Node::addChild(Node& child) {
	addChild(child.id);
}

void Node::activate() {
	Bromine::log(Logger::DEBUG, "Node %d is activating...", id);
	active = true;

	for (auto& trait : traits) {
		trait->activate();
	}
	
	for (auto it : children) {
		Bromine::node(it).activate();
	}
}

void Node::deactivate() {
	Bromine::log(Logger::DEBUG, "Node %d is deactivating...", id);
	active = false;

	for (auto& trait : traits) {
		trait->deactivate();
	}
	
	for (auto it : children) {
		Bromine::node(it).deactivate();
	}
}

bool Node::isActive() const {
	return active;
}

// bool Node::hasCapability(std::type_index capability) {
// 	return capabilities.find(capability) != capabilities.end();
// }

Vec2f& Node::position() {
	return _position;
}

Vec2f Node::position() const {
	return _position;
}

std::vector<NodeID> Node::getChildren() const {
	return children;
}

bool Node::hasChildren() const {
	return children.size() != 0;
}

} // namespace BromineEngine