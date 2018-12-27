#ifndef _NODE_H_
#define _NODE_H_

#include <cstdio>

namespace BromineEngine {

class Node {
friend class Scene;

protected:
	virtual void update();
	virtual void didEnterScene();

public:
	Node();
	~Node();
};

}

#endif //_NODE_H_