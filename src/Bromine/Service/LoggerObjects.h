#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace BromineEngine {

class Node;

std::ostream& operator<<(std::ostream& os, const Node& node);

}