#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <exception>

namespace BromineEngine {

struct BromineInitError : public std::exception {
	const char* message;
	
	BromineInitError(const char* message) : message(message) {}

	const char* what() const noexcept {
		return message;
	}
};

}

#endif // _ERRORS_H_