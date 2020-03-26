#include <Bromine/Bromine.h>
#include <Config/Config.h>
#include <Config/ServersConfig.h>
#include <Config/ServicesConfig.h>

using namespace BromineEngine;

const char *__asan_default_options() {
  return "verbosity=1:malloc_context_size=20";
}

int main(int argc, char const *argv[]) {
	Bromine bromine;
	Bromine::setGlobalInstance(&bromine);
	DEFAULT_SERVICE_REGISTRATION(bromine);
	DEFAULT_SERVER_REGISTRATION(bromine);

	return bromine.run(DEFAULT_INITIAL_SCENE);
}