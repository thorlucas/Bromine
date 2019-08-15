#include "Node.h"
#include "../Trait/Trait.h"
#include "../Scene/Scene.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {


Node::Node(NodeID id, const std::set<std::type_index> capabilities) : id(id), capabilities(capabilities) {}


Node::~Node() {
	// Deregister?
}

void Node::setParent(NodeID parent) {
	this->parent = parent;
	// TODO: If this already has a parent, tell the parent to remove this child
}

void Node::addChild(NodeID child) {
	Bromine::log(Logger::DEBUG, "Node %d added child node %d", id, child);
	children.insert(child);
	Bromine::node(child).setParent(id);
	// TODO: Notify capabilities
	// TODO: Notify scene
}

void Node::addChild(Node& child) {
	addChild(child.id);
}

void Node::activate() {
	Bromine::log(Logger::VERBOSE, "Node %d is activating...", id);
	for (auto it : capabilities) { // TODO: Faster to iterate by index, even in small numbers?
		Bromine::instance().getServer(it).activate(id);
	}
	for (auto it : children) {
		Bromine::node(it).activate();
	}
}

bool Node::hasCapability(std::type_index capability) {
	return capabilities.find(capability) != capabilities.end();
}

} // namespace BromineEngine