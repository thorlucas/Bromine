#include <Trait/PositionTrait.h>
#include <Node/Node.h>

namespace BromineEngine {

PositionTrait::PositionTrait() { }

void PositionTrait::init(Node* _owner) {
	owner = _owner;
}

PositionTrait::~PositionTrait() {}

Vector2<double> PositionTrait::globalPosition() {
	Node* p = owner->getParent();

	if (p != nullptr) {
		return position + p->positionTrait()->globalPosition();
	} else {
		return position;
	}
}

}