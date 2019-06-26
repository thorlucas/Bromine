#ifndef _NODE_SERVER_H_
#define _NODE_SERVER_H_

#include <map>

#include "Server.h"
#include "../Scene/Scene.h"
#include "../Node/Node.h"
#include "../Bromine.h"

namespace BromineEngine {

class NodeServer : public Server {
friend class Bromine;
private:
	NodeID nextAvailableID;
	std::map<NodeID, Node&> nodeMap;

protected:

public:
	NodeServer();
	~NodeServer();

	Node& getNode(NodeID id);

	template <typename N>
	N& createNode() {
		N& nref = *(new N(nextAvailableID++));
		nodeMap.insert(std::pair<NodeID, Node&>(nref.id, static_cast<Node&>(nref)));

		Bromine::log(Logger::VERBOSE, "Created node with ID %d: %p", nref.id, &nref);
		return nref;
	}

	void update() {}
	void activate(NodeID node) {}

};

}

#endif // _NODE_SERVER_H_