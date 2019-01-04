#include <BrAllocator.h>

namespace BromineEngine {

// TODO: Error handling!!!

BromineAllocator::BromineAllocator() {}

int BromineAllocator::init(size_t _stackSize) {
	stackSize = _stackSize;
	printf("Allocating %zu bytes\n", stackSize);
	stack = ::malloc(stackSize);
	head = (marker)stack;
	return 0;
}

BromineAllocator::~BromineAllocator() {
	::free(stack);
}

marker BromineAllocator::mark() {
	return head;
}

void* BromineAllocator::alloc(size_t size) {
	printf("Allocating %zu bytes\n", size);
	head += size;
	return (void*)head;
}

void BromineAllocator::free(marker m) {
	head = m;
}

} // namespace BromineEngine