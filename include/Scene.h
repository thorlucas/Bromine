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

	void preUpdate(); /**< The base update function. Do NOT overload. */
	void update(); /**< The update function, which can be overloaded. */
	
	void preDidPresent(); /** The base presentation to Bromine function. Do NOT overload. */
	/**
	 * This function is called when the scene
	 * is first added to Bromine and presented to
	 * the screen. You may overload this.
	 */
	void didPresent();

	
	void preInput(InputEvent& event);
	/**
	 * Called for each input event.
	 * @param event is a reference to the input event object.
	 */
	virtual void input(InputEvent& event);

public:
	Scene() : Scene(nullptr) {}
	Scene(Node* _root);
	~Scene();
	
};

} // namespace BromineEngine

#endif // _SCENE_H_