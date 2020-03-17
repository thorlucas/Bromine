#ifndef _NODE_SERVER_H_
#define _NODE_SERVER_H_

#include <unordered_map>

#include "Server.h"
#include "../Scene/Scene.h"
#include "../Node/Node.h"
#include "../Bromine.h"

namespace BromineEngine {

template <typename N>
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
template <typename N>
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
	 * @returns a reference to a new empty node (no traits) of type N.
	 */
	template <typename N, typename ...Ps>
	N& createEmptyNode(Ps&&... ps) {
		N& nref = *(new N(requestID(), ps...));
		nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

		Bromine::log(Logger::DEBUG, "Created node with ID %d: %p", nref.id, &nref);
		return nref;
	}

	/**
	 * @returns a reference to a new empty node (no traits).
	 */
	Node& createEmptyNode();

	/**
	 * Starts building a node of type N. This returns a pointer to the
	 * builder, and each subsequent call to the builder also returns a pointer,
	 * except the create() function. This means the node builder can be chained.
	 *
	 * @param ps the parameters passed to the new Node.
	 *
	 * @returns a pointer to the node builder.
	 */
	template <typename N, typename ...Ps>
	NodeBuilder<N>* buildNode(Ps&&... ps) {
		return new NodeBuilder<N>(*this, createEmptyNode<N>(ps...));
	}
};

/**
 * The node builder class is used to build up the traits
 * and properties of nodes.
 *
 * It can only be created by calling buildNode() or the
 * Bromine alias node().
 *
 * It's functions can all be chained together for ease of use,
 * for example:
 * Node& node = Bromine::node()
 *     ->trait<Foo>(fooArgs)
 *     ->trait<Bar>(barArgs)
 *	   ->position(Vec2f(100.0, 100.0))
 *     ->create()
 */
template <typename N>
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
	NodeBuilder* trait(Ps&&... ps) {
		node.addTrait<T>(ps...);

		return this;
	}

	/**
	 * Sets the node's position.
	 *
	 * @param position the new position of the node
	 * @returns the node builder itself for chaining
	 */
	NodeBuilder* position(Vec2f position) {
		node.position() = position;

		return this;
	}

	/**
	 * Creates the node.
	 *
	 * @returns a reference to the new node.
	 */
	N& create() {
		return node;
	}
};

}

#endif // _NODE_SERVER_H_