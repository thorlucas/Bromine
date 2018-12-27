#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include <string>
#include <SDL2/SDL.h>
#include <BrUtil.h>

namespace BromineEngine {

class Renderable {
private:
	SDL_Texture* texture;
	std::string resourceIdentifier;

	SDL_Rect srcRect;
	SDL_Rect dstRect;

public:
	Renderable(std::string, std::string);
	~Renderable();

	Vector2Ref position;
	Vector2 scale;

	SDL_Rect* getSrcRect();
	SDL_Rect* getDstRect();
	SDL_Texture* getTexture();
};

} // namespace BromineEngine

#endif // _RENDERABLE_H_