#ifndef _NODE_H_
#define _NODE_H_

#include <cstdio>
#include <vector>
#include <Event.h>
#include <BrAllocator.h>

namespace BromineEngine {

/**
 * Base node class from which all other nodes inherit.
 */
class Node {
friend class Scene;

protected:
	std::vector<Node*> children; /**< A list of the child nodes. */

	virtual void preUpdate(); /**< Base update function. Do NOT overload. */
	/**
	 * This function is called every main loop.
	 * This is the most common function to overload.
	 */
	virtual void update();

	virtual void preDidEnterScene(); /**< Base enter scene function. Do NOT overload. */
	/**
	 * This function is called when the scene is
	 * first presented to the screen. Overload this
	 * to prepare node for presentation.
	 */
	virtual void didEnterScene();

	virtual void preInput(InputEvent& event);
	virtual void input(InputEvent& event);

public:
	Node();
	~Node();

	/**
	 * Adds a child to the node.
	 * @param child is the child to add.
	 */
	void addChild(Node* child);
};

}

#endif //_NODE_H_