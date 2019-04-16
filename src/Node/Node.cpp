#include "Node.h"
#include "../Trait/Trait.h"
#include "../Scene/Scene.h"

namespace BromineEngine {


Node::Node(Scene& scene, NodeID id, NodeID parent) : scene(scene), id(id), parent(parent) {}
Node::Node(Scene& scene, NodeID id) : Node(scene, id, NODE_NULL) {}

Node::~Node() {
	// deregister child nodes from scene?
}

void Node::addChild(NodeID child) {
	children.push_back(child);
}

// void Node::registerTraits() {}

} // namespace BromineEngine