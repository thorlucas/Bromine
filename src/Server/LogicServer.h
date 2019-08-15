#ifndef _LOGIC_SERVER_H_
#define _LOGIC_SERVER_H_

#include "../Bromine.h"
#include "Server.h"

namespace BromineEngine {

class LogicTrait;

class LogicServer : public Server {
private:
	std::unordered_map<NodeID, LogicTrait&> nodeMap;
	std::set<NodeID> activeNodes;

public:
	void update();
	void activate(NodeID node);

	LogicTrait& getTrait(NodeID node);

	template <typename T, typename ...Ps>
	T& createTrait(NodeID node, Ps&&... ps) {
		T& tref = *(new T(node, std::forward<Ps>(ps)...));
		nodeMap.insert(std::pair<NodeID, LogicTrait&>(node, static_cast<LogicTrait&>(tref)));

		Bromine::log(Logger::DEBUG, "Created event trait for Node %d: %p", node, &tref);
		return tref;
	}
};

}

#endif // _LOGIC_SERVER_H_