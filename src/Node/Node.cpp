#include "Node.h"
#include "../Scene.h"

namespace BromineEngine {

Node::Node(Scene* scene, NodeID id) : scene(scene), id(id), parent(NODE_NULL) {
	scene->registerNode(this, id);
}

Node::Node(Scene* scene) : Node(scene, scene->requestNodeID()) {}

Node::~Node() {
	// deregister child nodes from scene?
}

// void Node::registerTraits() {}

} // namespace BromineEngine