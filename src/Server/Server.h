#ifndef _SERVER_H_
#define _SERVER_H_

#include "../Node/Node.h"
#include "../Trait/Trait.h"

namespace BromineEngine {

class Server {
public:
	Server() {};
	virtual ~Server() {};

	virtual void update() = 0;
};

}

#endif // _SERVER_H_