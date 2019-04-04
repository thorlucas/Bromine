#ifndef _TRAIT_H_
#define _TRAIT_H_

namespace BromineEngine {

typedef unsigned int TraitID;

class Trait {
public:
	Trait();
	virtual ~Trait() = 0;
};

}

#endif // _TRAIT_H_