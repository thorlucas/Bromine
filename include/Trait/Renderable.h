#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include <string>
#include <SDL2/SDL.h>
#include <BrUtil.h>

namespace BromineEngine {

class Renderable {
friend class Bromine;

private:
	SDL_Texture* texture;
	std::string resourceIdentifier;

	Recti srcRect;
	Recti dstRect;

protected:
	void _didEnterScene();

	Recti& getSrcRect();
	Recti& getDstRect();
	SDL_Texture* getTexture();

public:
	Renderable(std::string, std::string);
	~Renderable();

	Vector2Refi& position = dstRect.position;
	Vector2Refi& size = dstRect.size;

	void setScale(Vector2f scale);
	void setScale(float scale);
};

} // namespace BromineEngine

#endif // _RENDERABLE_H_