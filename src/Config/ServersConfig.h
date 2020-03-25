#pragma once

#include <Bromine/Server/NodeServer.h>
#include <Bromine/Server/RenderServer.h>
#include <Bromine/Server/EventServer.h>
#include <Bromine/Server/LogicServer.h>

// Register default servers here
#define DEFAULT_SERVER_REGISTRATION(instance)	\
instance.registerServer<NodeServer>();			\
instance.registerServer<RenderServer>();		\
instance.registerServer<EventServer>();			\
instance.registerServer<LogicServer>();			\
