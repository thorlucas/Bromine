#ifndef _SERVERS_CONFIG_H_
#define _SERVERS_CONFIG_H_

#include <vector>
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>

#include "../Server/Server.h"
#include "../Server/NodeServer.h"
#include "../Server/RenderServer.h"

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
	})
};

/**
 * List of server types that should be initiated on startup.
 */
static const std::vector<std::type_index> autoInitServers = {
	SERVER_TYPE(NodeServer),
	SERVER_TYPE(RenderServer)
};

}

#endif // _SERVERS_CONFIG_H_