#include "EventTrait.h"

namespace BromineEngine {

EventTrait::EventTrait(const NodeID owner) : Trait(owner), delegate(nullptr) {}
EventTrait::~EventTrait() {}

void EventTrait::setDelegate(EventDelegate* delegate) {
	this->delegate = delegate;
}

void EventTrait::onKeyEvent(const KeyboardEvent& event) {
	if (delegate != nullptr) {
		delegate->onKeyEvent(event);
	}
}

void EventTrait::onMouseEvent() {
	if (delegate != nullptr) {
		delegate->onMouseEvent();
	}
}

}