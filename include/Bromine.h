#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>

class Bromine {
private:
	Bromine();

	bool running;
	SDL_Window* window;

public:
	static Bromine& getInstance() {
		static Bromine instance;
		return instance;
	}

	Bromine(Bromine const&) = delete;
	void operator=(Bromine const&) = delete;

	int run();
};