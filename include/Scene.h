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

public:
	Scene(Node* pRoot);
	~Scene();
	
};

} // namespace BromineEngine

#endif // _SCENE_H_