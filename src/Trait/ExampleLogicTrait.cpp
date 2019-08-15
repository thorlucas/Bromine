#include "ExampleLogicTrait.h"
#include "SpriteRenderTrait.h"

namespace BromineEngine {

ExampleLogicTrait::ExampleLogicTrait(const NodeID owner) : LogicTrait(owner) {}
ExampleLogicTrait::~ExampleLogicTrait() {}

void ExampleLogicTrait::activate() {
	spritePosition = &getOwner().getTrait<SpriteRenderTrait>().position();
	getOwner().getTrait<EventTrait>().setDelegate(this);
}

void ExampleLogicTrait::update(double delta) {
	if (movingUp != movingDown) {
		(*spritePosition)[1] += movingDown ? 500.f * delta : -500.f * delta;
	}

	if (movingRight != movingLeft) {
		(*spritePosition)[0] += movingRight ? 500.f * delta : -500.f * delta;
	}
}

void ExampleLogicTrait::onKeyEvent(const KeyboardEvent& event) {
	switch (event.key) {
		case W:
			movingUp = event.state;
			break;
		case S:
			movingDown = event.state;
			break;
		case A:
			movingLeft = event.state;
			break;
		case D:
			movingRight = event.state;
			break;
		default:
			break;
	}
}

}