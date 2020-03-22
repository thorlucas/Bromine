#ifndef _NODE_SERVER_H_
#define _NODE_SERVER_H_

#include <unordered_map>

#include "Server.h"
#include "../Scene/Scene.h"
#include "../Node/Node.h"
#include "../Bromine.h"

namespace BromineEngine {

class NodeBuilder;

/**
 * This server manages the life cycle of nodes,
 * and maintains a map from node ID to node.
 *
 * This server should be the only one to ever delete
 * or create a node, hence why it returns references
 * instead of pointers.
 */
class NodeServer : public Server {
friend class Bromine;
friend class Node;
friend class NodeBuilder;
private:
	std::unordered_map<NodeID, Node&> nodeMap;

	NodeID nextAvailableID;

protected:
	NodeID requestID();
	void activate(NodeID node) {}
	void update(double delta) {}
	
public:
	NodeServer();
	~NodeServer();

	/**
	 * @returns a reference to the node requested.
	 */
	Node& getNode(NodeID id);

	/**
	 * @returns a reference to a new empty node (no traits).
	 */
	Node& createEmptyNode();

	/**
	 * Starts building a node of type N. This returns a pointer to the
	 * builder, and each subsequent call to the builder also returns a pointer,
	 * except the create() function. This means the node builder can be chained.
	*/
	NodeBuilder buildNode();

	void destroyNode(NodeID id);
};

class NodeBuilder {
friend class NodeServer;
private:
	NodeServer& nodeServer;
	Node& node;
	
protected:
	NodeBuilder(NodeServer& nodeServer, Node& emptyNode) : nodeServer(nodeServer), node(emptyNode) {}

public:
	/**
	 * Adds the trait T to the node being built.
	 * 
	 * @param ps are the parameters forwarded to the trait constructor
	 * @returns the node builder itself for chaining
	 */
	template <typename T, typename ...Ps>
	NodeBuilder& trait(Ps&&... ps) {
		node.addTrait<T>(ps...);

		return *this;
	}

	/**
	 * Sets the node's position.
	 *
	 * @param position the new position of the node
	 * @returns the node builder itself for chaining
	 */
	NodeBuilder& position(Vec2f position);

	NodeBuilder& addChild(Node& child);

	/**
	 * Creates the node.
	 *
	 * @returns a reference to the new node.
	 */
	Node& create();
};

}

#endif // _NODE_SERVER_H_