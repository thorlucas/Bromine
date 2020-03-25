#include <Bromine/Bromine.h>
#include <Config/Config.h>
#include <Config/ServersConfig.h>
#include <Config/ServicesConfig.h>

using namespace BromineEngine;

int main(int argc, char const *argv[]) {
	Bromine bromine;
	Bromine::setGlobalInstance(&bromine);
	DEFAULT_SERVER_REGISTRATION(bromine);
	DEFAULT_SERVICE_REGISTRATION(bromine);

	return bromine.run(DEFAULT_INITIAL_SCENE);
}