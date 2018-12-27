#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <Node/Node.h>
#include <Trait/Renderable.h>

namespace BromineEngine {

class Sprite : public Node, public Renderable {
protected:
	virtual void didEnterScene();

public:
	Sprite(std::string resourceIdentifier, std::string filePath);
	~Sprite();
};

} //namespace BromineEngine

#endif //_SPRITE_H_