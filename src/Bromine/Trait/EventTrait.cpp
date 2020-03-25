#include "EventTrait.h"

namespace BromineEngine {

DEFINE_BASE_TRAIT(EventTrait)

EventTrait::EventTrait(const NodeID owner) : CONSTRUCT_BASE_TRAIT(EventTrait), delegate(nullptr) {}
EventTrait::~EventTrait() {}

void EventTrait::setDelegate(EventDelegate* delegate) {
	Logger::debug("Set EventTrait {} delegate EventDelegate {}", static_cast<void*>(this), static_cast<void*>(delegate));
	this->delegate = delegate;
}

void EventTrait::onKeyEvent(const KeyboardEvent& event) {
	Logger::trace("EventTrait {} for Node {} got key press", static_cast<void*>(this), owner().id);
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