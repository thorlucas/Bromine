#ifndef _LOGIC_SERVER_H_
#define _LOGIC_SERVER_H_

#include "../Bromine.h"
#include "Server.h"

namespace BromineEngine {

class LogicTrait;

class LogicServer : public Server {
DECLARE_TRAIT_SERVER(LogicServer, LogicTrait)
DEFINE_TRAIT_SERVER_CREATE_TRAIT_STANDARD(LogicTrait)
public:
	LogicServer();

	void update(double delta);

};

}

#endif // _LOGIC_SERVER_H_