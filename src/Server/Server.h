#ifndef _SERVER_H_
#define _SERVER_H_

#include <unordered_map>
#include "../Node/Node.h"

namespace BromineEngine {

class Server {
public:
	Server() {};
	virtual ~Server() {};

	virtual void update(double delta) = 0;
	virtual void activate(NodeID node) = 0;

	virtual void nodeAddedChild(NodeID parent, NodeID child) {};
};

}

#endif // _SERVER_H_