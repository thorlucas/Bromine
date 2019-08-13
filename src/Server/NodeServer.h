#ifndef _NODE_SERVER_H_
#define _NODE_SERVER_H_

#include <unordered_map>

#include "Server.h"
#include "../Scene/Scene.h"
#include "../Node/Node.h"
#include "../Bromine.h"

namespace BromineEngine {

class NodeServer : public Server {
friend class Bromine;
friend class Node;
private:
	std::unordered_map<NodeID, Node&> nodeMap;

	NodeID nextAvailableID;

protected:
	NodeID requestID();
	void activate(NodeID node) {}
	
	void update() {}
	
public:
	NodeServer();
	~NodeServer();

	Node& getNode(NodeID id);

	// TODO: Replace with a builder?
	template <typename N, typename ...Ts, typename ...Ps>
	N& createNode(Ps&&... ps) {
		N& nref = *(new N(requestID(), std::set<std::type_index>({typeid(typename Ts::serverType)...}), std::forward<Ps>(ps)...));
		nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

		// TODO: Is this dummy necessary?
		void* dummy[sizeof...(Ts)] = { static_cast<void*>(&(Bromine::server<typename Ts::serverType>().template createTrait<Ts>(nref.id)))... };

		Bromine::log(Logger::DEBUG, "Created node with ID %d: %p", nref.id, &nref);
		return nref;
	}

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
			// TODO: Check if inserted
			return this;
		}

		N& create() {
			return nodeServer.createNodeFromBuilder<N>(this);
		}

	};

	template <typename N>
	NodeBuilder<N>* buildNode() {
		return new NodeBuilder<N>(*this, requestID());
	}

	template <typename N>
	N& createNodeFromBuilder(NodeBuilder<N>* builder) {
		N& nref = *(new N(builder->nodeID, builder->capabilities));
		nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

		delete builder;

		Bromine::log(Logger::DEBUG, "Created node with ID %d: %p", nref.id, &nref);
		return nref;
	}
};

}

#endif // _NODE_SERVER_H_