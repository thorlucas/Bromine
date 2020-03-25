#include "Node.h"
#include "../Trait/Trait.h"
#include "../Scene/Scene.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {


Node::Node(NodeID id) : id(id), _enabled(true), _parentIsActive(false), _parent(NODE_NULL) {}

Node::~Node() {}

void Node::setParent(NodeID newParentID) {
	if (newParentID == NODE_NULL) {
		if (_parent != NODE_NULL && parent().active())
			parentDidDeactivate();

		_parent = newParentID;
		return;
	}

	Node& newParent = Bromine::node(newParentID);

	if (_parent != NODE_NULL) {
		Node& oldParent = parent();
		oldParent.removeChild(*this);

		if (oldParent.active() && !newParent.active())
			parentDidDeactivate();
		else if (!oldParent.active() && newParent.active())
			parentDidActivate();
	} else {
		if (newParent.active())
			parentDidActivate();
	}

	_parent = newParentID;
}

void Node::addChild(NodeID child) {
	addChild(Bromine::node(child));
}

void Node::addChild(Node& child) {
	_children.push_back(child.id);
	child.setParent(id);

	Bromine::log(Logger::DEBUG, "Node %d added child node %d", id, child.id);
}

void Node::removeChild(NodeID child) {
	removeChild(Bromine::node(child));
}

void Node::removeChild(Node& child) {
	_children.erase(std::find(_children.begin(), _children.end(), child.id));
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
	
	for (auto child : children()) {
		child->parentDidActivate();
	}
}

void Node::bubbleDeactivate() {
	for (auto& trait : traits) {
		trait->ownerDidDeactivate();
	}

	for (auto child : children()) {
		child->parentDidDeactivate();
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

std::vector<Node*> Node::children() const {
	std::vector<Node*> childrenRefs;
	for (auto childID : _children) {
		childrenRefs.push_back(&Bromine::node(childID));
	}
	return childrenRefs;
}

bool Node::hasChildren() const {
	return _children.size() != 0;
}

Node& Node::parent() const {
	return Bromine::node(_parent);
}

void Node::destroy() {
	parent().removeChild(*this);

	for (auto& trait : traits) {
		trait->destroy();
	}

	Bromine::server<NodeServer>().destroyNode(id);
}

} // namespace BromineEngine