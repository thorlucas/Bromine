#ifndef _CONFIG_SERVER_H_
#define _CONFIG_SERVER_H_

#include <vector>
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>

#include <Bromine/Server/Server.h>
#include <Bromine/Server/NodeServer.h>
#include <Bromine/Server/RenderServer.h>
#include <Bromine/Server/EventServer.h>
#include <Bromine/Server/LogicServer.h>

#define REG_SERVER(name, function) { typeid(name), function }
#define SERVER_TYPE(name) typeid(name)

namespace BromineEngine {

/**
 * This map defines the closures that should be automatically loaded.
 */
const std::unordered_map<std::type_index, std::function<Server*()>> autoloadServerClosures = {
	REG_SERVER(NodeServer, [] {
		return new NodeServer;
	}),
	REG_SERVER(RenderServer, [] {
		return new RenderServer;
	}),
	REG_SERVER(EventServer, [] {
		return new EventServer;
	}),
	REG_SERVER(LogicServer, [] {
		return new LogicServer;
	})
};

/**
 * List of server types that should be initiated on startup.
 */
const std::vector<std::type_index> autoInitServers = {
	SERVER_TYPE(NodeServer),
	SERVER_TYPE(RenderServer),
	SERVER_TYPE(EventServer),
	SERVER_TYPE(LogicServer)
};

}

#endif // _CONFIG_SERVER_H_