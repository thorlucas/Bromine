#ifndef _NODE_H_
#define _NODE_H_

#include <map>
#include <vector>
#include <cstdint>
#include <cstdio>

#include "../Trait/Trait.h"

namespace BromineEngine {

typedef uint32_t NodeID;
#define NODE_NULL INT32_MAX

class Scene;

class Node {
friend class Scene;
protected:
	// std::vector<TraitID> traits;

	// Scenes own all nodes that have been registered
	NodeID parent; /**< Parent node, NODE_NULL if root. */
	std::vector<NodeID> children; /**< A list of the child nodes. */

	// void registerTraits(); /**< Called by scene load, registers components to server. */

public:
	const Scene* scene;
	const NodeID id; /**< A constant ID, which should be requested from the scene. */

	Node(Scene* scene, NodeID id); /**< Assigns an ID. Failable? */
	Node(Scene* scene); /**< Automatically requests an ID from scene. */

	~Node();

	// bool attachTrait(Trait* trait);
};

}

#endif //_NODE_H_