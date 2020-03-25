#include "LoggerObjects.h"
#include <Bromine/Node/Node.h>

namespace BromineEngine {

std::ostream& operator<<(std::ostream& os, const Node& node) {
	return os << fmt::format("Node {} ({})", node.id, static_cast<const void*>(&node));
}

}