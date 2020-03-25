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

	Logger::debug("{} added child {}", *this, child);
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
	Logger::debug("{} is being enabled...", *this);
	_enabled = true;

	if (_parentIsActive)
		bubbleActivate();
}

void Node::disable() {
	Logger::debug("{} is being disabled...", *this);
	_enabled = false;

	if (_parentIsActive)
		bubbleDeactivate();
}

void Node::parentDidActivate() {
	_parentIsActive = true;

	 // If we ourselves are not enabled, we shouldn't activate our traits and children
	if (_enabled) {
		Logger::debug("{} is activating by bubbling...", *this);
		bubbleActivate();
	}
}

void Node::parentDidDeactivate() { 
	_parentIsActive = false;

	// If we are already not active, no need to call this again
	if (_enabled) {
		Logger::debug("{} is deactivating by bubbling...", *this);
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