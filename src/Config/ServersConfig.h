#ifndef _SERVERS_CONFIG_H_
#define _SERVERS_CONFIG_H_

#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>

#include "../Server/Server.h"
#include "../Server/RenderServer.h"

namespace BromineEngine {

/**
 * This map defines the closures that should be automatically loaded.
 */
static const std::unordered_map<std::type_index, std::function<Server*()>> autoloadServerClosures = {
	{ typeid(RenderServer), [] {
		return new RenderServer;
	}} //,
//	{ typeid(ExampleServer) : [] {
//		return new ExampleServer(parameters);
//	}}
};

}

#endif // _SERVERS_CONFIG_H_