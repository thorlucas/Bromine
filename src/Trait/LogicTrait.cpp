#include "LogicTrait.h"

namespace BromineEngine {

LogicTrait::LogicTrait(const NodeID owner) : Trait(owner) {}
LogicTrait::~LogicTrait() {}

void LogicTrait::activate() {}
void LogicTrait::update(double delta) {}

}