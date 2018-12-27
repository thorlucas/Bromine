#include <Bromine.h>
#include <Trait/Renderable.h>

namespace BromineEngine {

Renderable::Renderable(std::string _resourceIdentifier, std::string resourcePath) : resourceIdentifier(_resourceIdentifier) {
	texture = Bromine::Resource()->getTexture(resourceIdentifier, resourcePath);

	SDL_QueryTexture(texture, NULL, NULL, &(srcRect.w), &(srcRect.h));
	dstRect.w = srcRect.w; dstRect.h = srcRect.h;
}

Renderable::~Renderable() {
	Bromine::Resource()->freeResource(resourceIdentifier);
}

void Renderable::_didEnterScene() {
	Bromine::getInstance().addRenderable(this);
}

Rect& Renderable::getSrcRect() {
	return srcRect;
}

Rect& Renderable::getDstRect() {
	// TODO: Use scale
	return dstRect;
}

SDL_Texture* Renderable::getTexture() {
	return texture;
}

} // namespace BromineEngine