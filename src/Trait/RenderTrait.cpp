#include "RenderTrait.h"

#include "../Bromine.h"

namespace BromineEngine {

DEFINE_BASE_TRAIT(RenderTrait)

RenderTrait::RenderTrait(const NodeID owner) : CONSTRUCT_BASE_TRAIT(RenderTrait) {}

RenderTrait::~RenderTrait() {}

void RenderTrait::render() {}

}