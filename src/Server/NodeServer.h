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

// TODO: Move non templated definitions to cpp file
class NodeServer : public Server {
friend class Bromine;
friend class Node;
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

	Node& getNode(NodeID id);

	template <typename N>
	N& createEmptyNode() {
		N& nref = *(new N(requestID(), std::set<std::type_index>()));
		nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

		Bromine::log(Logger::DEBUG, "Created node with ID %d: %p", nref.id, &nref);
		return nref;
	}

	Node& createEmptyNode() {
		Node& nref = *(new Node(requestID(), std::set<std::type_index>()));
		nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

		Bromine::log(Logger::DEBUG, "Created node with ID %d: %p", nref.id, &nref);
		return nref;
	}

	template <typename N>
	NodeBuilder<N>* buildNode() {
		return new NodeBuilder<N>(*this, requestID());
	}

	NodeBuilder<Node>* buildNode() {
		return buildNode<Node>();
	}

	// TODO: I don't think we need another function for this
	template <typename N>
	N& createNodeFromBuilder(NodeBuilder<N>* builder) {
		N& nref = *(new N(builder->nodeID, builder->capabilities));
		nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

		delete builder;

		Bromine::log(Logger::DEBUG, "Created node with ID %d: %p", nref.id, &nref);
		return nref;
	}

	template <typename N, typename ...Ps>
	N& createNodeFromBuilder(NodeBuilder<N>* builder, Ps&&... ps) {
		N& nref = *(new N(builder->nodeID, builder->capabilities, std::forward(ps...)));
		nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

		delete builder;

		Bromine::log(Logger::DEBUG, "Created node with ID %d: %p", nref.id, &nref);
		return nref;
	}
};

template <typename N>
class NodeBuilder {
friend class NodeServer;
private:
	NodeServer& nodeServer;
	
protected:
	const NodeID nodeID;
	std::set<std::type_index> capabilities;

	NodeBuilder(NodeServer& nodeServer, const NodeID nodeID) : nodeServer(nodeServer), nodeID(nodeID) {};

public:
	template <typename T, typename ...Ps>
	NodeBuilder* addTrait(Ps&&... ps) {
		T& trait = Bromine::server<typename T::serverType>().template createTrait<T>(nodeID, std::forward<Ps>(ps)...);
		auto ret = capabilities.insert(typeid(typename T::serverType));
		
		if (!ret.second) throw std::invalid_argument("Node builder can't add multiple traits for the same server.");

		return this;
	}

	N& create() {
		return nodeServer.createNodeFromBuilder<N>(this);
	}

	template <typename ...Ps>
	N& create(Ps&&... ps) {
		return nodeServer.createNodeFromBuilder<N>(this, std::forward<Ps>(ps)...);
	}
};

}

#endif // _NODE_SERVER_H_