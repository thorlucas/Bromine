#include <Bromine.h>
#include <Trait/Renderable.h>

namespace BromineEngine {

Renderable::Renderable(std::string _resourceIdentifier, std::string resourcePath) : resourceIdentifier(_resourceIdentifier), position(dstRect.x, dstRect.y), scale(1, 1) {
	texture = Bromine::Resource()->getTexture(resourceIdentifier, resourcePath);

	srcRect.x = 0; srcRect.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &(srcRect.w), &(srcRect.h));

	dstRect.x = 0; dstRect.y = 0;
	dstRect.w = srcRect.w; dstRect.h = srcRect.h;
}

Renderable::~Renderable() {
	Bromine::Resource()->freeResource(resourceIdentifier);
}

void Renderable::_didEnterScene() {
	Bromine::getInstance().addRenderable(this);
}

SDL_Rect* Renderable::getSrcRect() {
	return &srcRect;
}

SDL_Rect* Renderable::getDstRect() {
	// TODO: Use scale
	return &dstRect;
}

SDL_Texture* Renderable::getTexture() {
	return texture;
}

} // namespace BromineEngine