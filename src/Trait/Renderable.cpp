#include <Bromine.h>
#include <Trait/Renderable.h>

namespace BromineEngine {

Renderable::Renderable(std::string _resourceIdentifier, std::string resourcePath) : resourceIdentifier(_resourceIdentifier) {
	texture = Bromine::resourceManager().getTexture(resourceIdentifier, resourcePath);

	SDL_QueryTexture(texture, NULL, NULL, &(srcRect.w), &(srcRect.h));
	dstRect.size = srcRect.size;
}

Renderable::~Renderable() {
	Bromine::resourceManager().freeResource(resourceIdentifier);
}

void Renderable::preDidEnterScene() {
	Bromine::instance().addRenderable(this);
}

Recti& Renderable::getSrcRect() {
	return srcRect;
}

Recti& Renderable::getDstRect() {
	// TODO: Use scale
	return dstRect;
}

SDL_Texture* Renderable::getTexture() {
	return texture;
}

void Renderable::setScale(Vector2f scale) {
	dstRect.size.w = scale.w * srcRect.size.w;
	dstRect.size.h = scale.h * srcRect.size.h;
}

void Renderable::setScale(float scale) {
	dstRect.size = scale * srcRect.size;
}

} // namespace BromineEngine