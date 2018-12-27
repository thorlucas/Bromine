#ifndef _SCENE_H_
#define _SCENE_H_

#include <Node/Node.h>

namespace BromineEngine {

class Scene {
friend class Bromine;

private:
	Node* root;

protected:
	void update();
	void didPresent();

public:
	Scene(Node* _root);
	~Scene();
	
};

} // namespace BromineEngine

#endif // _SCENE_H_