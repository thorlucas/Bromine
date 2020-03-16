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

	// TODO: I don't think we need another function for this
	// template <typename N>
	// N& createNodeFromBuilder(NodeBuilder<N>* builder) {
	// 	N& nref = *(new N(builder->nodeID, builder->capabilities));
	// 	nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

	// 	delete builder;

	// 	Bromine::log(Logger::DEBUG, "Created node with ID %d: %p", nref.id, &nref);
	// 	return nref;
	// }

	// template <typename N, typename ...Ps>
	// N& createNodeFromBuilder(NodeBuilder<N>* builder, Ps&&... ps) {
	// 	N& nref = *(new N(builder->nodeID, builder->capabilities, std::forward(ps...)));
	// 	nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

	// 	delete builder;

	// 	Bromine::log(Logger::DEBUG, "Created node with ID %d: %p", nref.id, &nref);
	// 	return nref;
	// }
	
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
	template <typename N>
	N& createEmptyNode() {
		N& nref = *(new N(requestID()));
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
	 * TODO: Replace with a reference so that it cant be acci
	 *
	 * @returns a pointer to the node builder.
	 */
	// template <typename N>
	// NodeBuilder<N>* buildNode() {
	// 	return new NodeBuilder<N>(*this, requestID());
	// }

	/**
	 * Starts building a node. See buildNode<N>().
	 *
	 * @returns a pointer to the node builder.
	 */
	// NodeBuilder<Node>* buildNode();
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
 *     ->addTrait<Foo>(fooArgs)
 *     ->addTrait<Bar>(barArgs)
 *     ->create()
 */
// template <typename N>
// class NodeBuilder {
// friend class NodeServer;
// private:
// 	NodeServer& nodeServer;
	
// protected:
// 	const NodeID nodeID;
// 	std::set<std::type_index> capabilities;

// 	NodeBuilder(NodeServer& nodeServer, const NodeID nodeID) : nodeServer(nodeServer), nodeID(nodeID) {};

// public:
// 	/**
// 	 * Adds the trait T to the node being built.
// 	 * 
// 	 * @param ps are the parameters forwarded to the trait constructor
// 	 * @returns the node builder itself for chaining
// 	 */
// 	template <typename T, typename ...Ps>
// 	NodeBuilder* addTrait(Ps&&... ps) {
// 		T& trait = Bromine::server<typename T::serverType>().template createTrait<T>(nodeID, std::forward<Ps>(ps)...);
// 		auto ret = capabilities.insert(typeid(typename T::serverType));
		
// 		// TODO: Why not?
// 		if (!ret.second) throw std::invalid_argument("Node builder can't add multiple traits for the same server.");

// 		return this;
// 	}

// 	/**
// 	 * Creates the node.
// 	 *
// 	 * @returns a reference to the new node.
// 	 */
// 	N& create() {
// 		return nodeServer.createNodeFromBuilder<N>(this);
// 	}

// 	/**
// 	 * Creates the node with parameters.
// 	 *
// 	 * @param ps are the parameters forwarded to the node's constructor.
// 	 * @returns a reference to the new node.
// 	 */
// 	template <typename ...Ps>
// 	N& create(Ps&&... ps) {
// 		return nodeServer.createNodeFromBuilder<N>(this, std::forward<Ps>(ps)...);
// 	}
// };

}

#endif // _NODE_SERVER_H_