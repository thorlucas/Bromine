#include "Node.h"
#include "../Trait/Trait.h"
#include "../Scene/Scene.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {


Node::Node(NodeID id) : id(id), _enabled(true), _parentIsActive(false), parent(NODE_NULL) {}

Node::~Node() {}

void Node::setParent(NodeID newParent) {
	if (newParent == NODE_NULL) {
		if (parent != NODE_NULL && Bromine::node(parent).active())
			parentDidDeactivate();

		parent = newParent;
		return;
	}

	Node& newParentRef = Bromine::node(newParent);

	if (parent != NODE_NULL) {
		Node& oldParentRef = Bromine::node(parent);
		oldParentRef.removeChild(*this);

		if (oldParentRef.active() && !newParentRef.active())
			parentDidDeactivate();
		else if (!oldParentRef.active() && newParentRef.active())
			parentDidActivate();
	} else {
		if (newParentRef.active())
			parentDidActivate();
	}

	parent = newParent;
}

void Node::addChild(NodeID child) {
	addChild(Bromine::node(child));
}

void Node::addChild(Node& child) {
	children.push_back(child.id);
	child.setParent(id);

	Bromine::log(Logger::DEBUG, "Node %d added child node %d", id, child.id);
}

void Node::removeChild(NodeID child) {
	removeChild(Bromine::node(child));
}

void Node::removeChild(Node& child) {
	children.erase(std::find(children.begin(), children.end(), child.id));
	child.setParent(NODE_NULL);
}

void Node::removeTrait(Trait* trait) {
	trait->destroy();
	traits.erase(std::find(traits.begin(), traits.end(), trait));
}

void Node::enable() {
	Bromine::log(Logger::DEBUG, "Node %d is being enabled...", id);
	_enabled = true;

	if (_parentIsActive)
		bubbleActivate();
}

void Node::disable() {
	Bromine::log(Logger::DEBUG, "Node %d is being disabled...", id);
	_enabled = false;

	if (_parentIsActive)
		bubbleDeactivate();
}

void Node::parentDidActivate() {
	_parentIsActive = true;

	 // If we ourselves are not enabled, we shouldn't activate our traits and children
	if (_enabled) {
		Bromine::log(Logger::DEBUG, "Node %d is activating by bubbling...", id);
		bubbleActivate();
	}
}

void Node::parentDidDeactivate() { 
	_parentIsActive = false;

	// If we are already not active, no need to call this again
	if (_enabled) {
		Bromine::log(Logger::DEBUG, "Node %d is deactivating by bubbling...", id);
		bubbleDeactivate();
	}
}

void Node::bubbleActivate() {
	for (auto& trait : traits) {
		trait->ownerDidActivate();
	}
	
	for (auto child : children) {
		Bromine::node(child).parentDidActivate();
	}
}

void Node::bubbleDeactivate() {
	for (auto& trait : traits) {
		trait->ownerDidDeactivate();
	}

	for (auto children : children) {
		Bromine::node(children).parentDidDeactivate();
	}
}

bool Node::active() const {
	return _enabled && _parentIsActive;
}

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

void Node::destroy() {
	Bromine::node(parent).removeChild(*this);

	for (auto& trait : traits) {
		trait->destroy();
	}

	Bromine::instance().nodeServer.destroyNode(id);
}

} // namespace BromineEngine