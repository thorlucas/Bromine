#include "../../src/Bromine.h"
#include "../../src/Server/RenderServer.h"
#include "../../src/Factory/SpriteFactory.h"

using namespace BromineEngine;

int main(int argc, char const *argv[]) {
	// SpriteFactory factory;

	// Bromine::instance().registerServer<RenderServer>(RenderServer::instance());
	// Bromine::instance().registerFactory<SpriteFactory>(factory);

	// printf("Registered\n");

	// Scene* scene = new Scene;
	// Node* node = Bromine::instance().getFactory<SpriteFactory>()(scene);

	// printf("Got\n");

	printf("About to register\n");

	Bromine::instance().registerServer<RenderServer>([] {
		return new RenderServer;
	});

	printf("Registered\nAbout to get\n");

	Bromine::instance().getServer<RenderServer>();

	printf("Got\nGetting again\n");

	Bromine::instance().getServer<RenderServer>();
		
	printf("Got\n");

	// Bromine::instance<RenderServer>();
	// Bromine::instance<SpriteFactory>();

	// Scene* scene = new Scene;
	// Node* node = Bromine::instance<SpriteFactory>()(scene);

	return 0;
}