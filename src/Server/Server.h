#ifndef _SERVER_H_
#define _SERVER_H_

#include "../Node/Node.h"

namespace BromineEngine {

class Server {
public:
	Server() {};
	virtual ~Server() {};

	virtual void update() = 0;

	virtual void test() {
		printf("Testing from base\n");
	}
};

}

#endif // _SERVER_H_