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

	Rect srcRect;
	Rect dstRect;

protected:
	void _didEnterScene();

public:
	Renderable(std::string, std::string);
	~Renderable();

	Vector2Ref& position = dstRect.position;
	Vector2Ref& size = dstRect.size;

	Rect& getSrcRect();
	Rect& getDstRect();
	SDL_Texture* getTexture();
};

} // namespace BromineEngine

#endif // _RENDERABLE_H_