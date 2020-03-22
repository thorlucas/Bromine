#include "Trait.h"

namespace BromineEngine {

const std::size_t Trait::type = std::hash<std::string>()("Trait");

bool Trait::active() const {
	return _enabled && _ownerIsActive;
}

void Trait::enable() {
	_enabled = true;

	if (_ownerIsActive)
		notifyActivate();
}

void Trait::disable() {
	_enabled = false;

	if (_ownerIsActive)
		notifyDeactivate();
}

void Trait::ownerDidActivate() {
	_ownerIsActive = true;

	if (_enabled)
		notifyActivate();
}

void Trait::ownerDidDeactivate() {
	_ownerIsActive = false;

	if (_enabled)
		notifyDeactivate();
}

}