#ifndef _CONFIG_SERVER_H_
#define _CONFIG_SERVER_H_

#include <vector>
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>

#include "../Server/Server.h"
#include "../Server/NodeServer.h"
#include "../Server/RenderServer.h"
#include "../Server/EventServer.h"
#include "../Server/LogicServer.h"

#define REG_SERVER(name, function) { typeid(name), function }
#define SERVER_TYPE(name) typeid(name)

namespace BromineEngine {

/**
 * This map defines the closures that should be automatically loaded.
 */
static const std::unordered_map<std::type_index, std::function<Server*()>> autoloadServerClosures = {
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
static const std::vector<std::type_index> autoInitServers = {
	SERVER_TYPE(NodeServer),
	SERVER_TYPE(RenderServer),
	SERVER_TYPE(EventServer),
	SERVER_TYPE(LogicServer)
};

}

#endif // _CONFIG_SERVER_H_