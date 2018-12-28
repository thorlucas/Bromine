#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include <string>
#include <SDL2/SDL.h>
#include <BrUtil.h>

namespace BromineEngine {

/**
 * This is a trait inherited by nodes which are
 * rendered to the screen by Bromine.
 */
class Renderable {
friend class Bromine;

private:
	/**
	 * A pointer to the texture to be presented.
	 * Note: This class is NOT the owner. Do not
	 * free this texture on destructor.
	 */
	SDL_Texture* texture;
	std::string resourceIdentifier; /**< The identifier used by ResourceManager. */

	Recti srcRect; /**< A rectangle representing the source area of the texture to be rendered. */
	Recti dstRect; /**< A rectangle representing the destination area of the screen to be rendered to. */

protected:
	void preDidEnterScene(); /**< Base did enter scene. Do NOT overload. */

	Recti& getSrcRect(); /**< Used by Bromine to get the source rectangle for rendering. */
	Recti& getDstRect(); /**< Used by Bromine to get the desination rectangle for rendering. */
	SDL_Texture* getTexture(); /**< Used by Bromine to get the texture for rendering. */

public:
	/**
	 * Creates a renderable item with a texture
	 * @param identifier is the ID used by the ResourceManager.
	 * @param filePath is the path of the image file.
	 */
	Renderable(std::string, std::string);
	~Renderable();

	Vector2Refi& position = dstRect.position; /**< A reference vector to the position on the screen. */
	Vector2Refi& size = dstRect.size; /**< A reference vector to the size on the screen. */

	/**
	 * Scales the size on the screen based on the source size.
	 * @param scale is a vector of the x and y components of the scaling.
	 */
	void setScale(Vector2f scale);
	void setScale(float scale); /**< Scales the vector by an equal amount on the x and y directions. */
};

} // namespace BromineEngine

#endif // _RENDERABLE_H_