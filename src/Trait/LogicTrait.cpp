#include "LogicTrait.h"

namespace BromineEngine {

DEFINE_BASE_TRAIT(LogicTrait)

LogicTrait::LogicTrait(const NodeID owner) : CONSTRUCT_BASE_TRAIT(LogicTrait) {}
LogicTrait::~LogicTrait() {}

void LogicTrait::update(double delta) {}

}