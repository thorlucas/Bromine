#include "EventTrait.h"

namespace BromineEngine {

DEFINE_BASE_TRAIT(EventTrait)

EventTrait::EventTrait(const NodeID owner) : CONSTRUCT_BASE_TRAIT(EventTrait), delegate(nullptr) {}
EventTrait::~EventTrait() {}

void EventTrait::setDelegate(EventDelegate* delegate) {
	Bromine::log(Logger::DEBUG, "Set EventTrait %p delegate EventDelegate %p", this, delegate);
	this->delegate = delegate;
}

void EventTrait::onKeyEvent(const KeyboardEvent& event) {
	Bromine::log(Logger::VERBOSE, "EventTrait %p for Node %d got key press", this, owner().id);
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