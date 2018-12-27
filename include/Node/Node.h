#ifndef _NODE_H_
#define _NODE_H_

#include <cstdio>
#include <vector>

namespace BromineEngine {

class Node {
friend class Scene;

protected:
	std::vector<Node*> children;

	virtual void _update();
	virtual void update();

	virtual void _didEnterScene();
	virtual void didEnterScene();

public:
	Node();
	~Node();

	void addChild(Node* child);
};

}

#endif //_NODE_H_