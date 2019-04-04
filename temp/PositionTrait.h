#ifndef _POSITION_TRAIT_H_
#define _POSITION_TRAIT_H_

#include <BrUtil.h>

namespace BromineEngine {

class Node;

class PositionTrait {
protected:
	Node* owner;

public:
	PositionTrait();
	void init(Node* _owner); // TODO: Protect to Node (owner)?

	~PositionTrait();

	Vector2<double> position; /**< Position relative to parent node, or to world if root node. */

	// TODO: Consider cacheing this
	Vector2<double> globalPosition();	
};

} // namespace BromineEngine

#endif // _POSITION_TRAIT_H_