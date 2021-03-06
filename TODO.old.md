# Restructure Responsbilities Branch

## Goals

- Make `Node` and `Scene` dumb. 
- These two should just be merely container objects.
- `Node`s can:
	- Hold `Trait` pointers
	- Hold a pointer to the `Scene` they're in (or `nullptr`)
	- Have a transform
	- Keep track of parents and children
	- Should be final
		- Factories can be used to set up custom nodes
		- This also allows prefabs to exist!
		- A factory is a sort of prefab!
	- Deactivate and activate (updates only their own bool!)
	- Be destroyed, which removes the Node from the scene, calls destroy on the `Trait`s and on `NodeServer`.
- `NodeServer` can then:
	- Not require templates for creating nodes 
	- Not require parameters for instantiation of nodes
- All `Server`s can:
	- Loop through current Scene tree
	- Skip deactivated `Node` branches
	- If tree traversal is too slow we could also:
		- Send a `parentDidDeactivate()` message through node tree
		- This calls the trait's `ownerDidDeactivate()`
		- The trait calls the server's `deactivateTrait()`
		- This allows manual trait deactivation and bubbling deactivation to appear the same to the server
	- `Server`s could keep track of traits in a linear vector by:
		- Traversing tree when `dirtyFlag` is set, pushing to vector
		- `dirtyFlag` is set when `deactivateTrait()` or `activateTrait()` is called
		- Works with node deactivation bubbling
- `Scene`s need:
	- Iterators through all of it's `Node`s
	- This is done by keeping track of only the `rootNode`
	- Iterator comparation could be done by just the `NodeID` which it points to! (fast!)
	- For Scene initialization we can:
		- Allow a `loadScene()` override
		- Or simply pass a functor to a scene, which:
			- Discourages storing state in the scene itself
			- Discourages misusing scene
			- Keeps scenes dumb
			- But where would you pass the functor?
		- Scenes could be a good place to keep track of node information and do scene behavior...
			- It seems more intuitive than using some random node's logic trait
			- More intuitive than having a node handle scene changes
- Recompile when headers are changed
- A lot of configs could be replaced with macro for better optimization