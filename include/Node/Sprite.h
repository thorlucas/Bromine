#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <Node/Node.h>
#include <Trait/Renderable.h>

namespace BromineEngine {

/**
 * This is a basic sprite node, consisting of
 * an image in a location on the screen.
 */
class Sprite : public Node, public Renderable {
protected:
	virtual void _didEnterScene(); /**< Do NOT overload. */

public:
	/**
	 * Creates the sprite with an identifier and a path.
 	 * @param identifier is the ID used by the ResourceManager.
	 * @param filePath is the path of the image file.
	 */
	Sprite(std::string resourceIdentifier, std::string filePath);
	~Sprite();
};

} //namespace BromineEngine

#endif //_SPRITE_H_