#ifndef _BR_ALLOCATOR_H_
#define _BR_ALLOCATOR_H_

#include <cstdlib>
#include <cstdio>
#include <cstdint>

namespace BromineEngine {

typedef uint64_t marker;

class BromineAllocator {
private:
	void* stack;
	size_t stackSize;

	marker head;
public:
	BromineAllocator();
	~BromineAllocator();

	int init(size_t _stackSize);
	
	marker mark();
	void* alloc(size_t size);
	void free(marker m);
};

} // namespace BromineEngine

#endif // _BR_ALLOCATOR_H_