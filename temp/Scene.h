#ifndef _SCENE_H_
#define _SCENE_H_

#include <Event.h>
#include <Node/Node.h>

namespace BromineEngine {

/**
 * This is the base scene class.
 * You should derive scenes from this to set
 * up the node tree, etc.
 */
class Scene {
friend class Bromine;

protected:
	Node* root; /**< The root node which will be called for update, didEnterScene, etc. */

public:
	Scene() : Scene(nullptr) {}
	Scene(Node* _root);
	~Scene();
	
};

} // namespace BromineEngine

#endif // _SCENE_H_