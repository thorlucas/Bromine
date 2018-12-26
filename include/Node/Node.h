#ifndef _NODE_H_
#define _NODE_H_

namespace BromineEngine {

class Node {
friend class Scene;

protected:
	void update();

public:
	Node();
	~Node();
};

}

#endif //_NODE_H_