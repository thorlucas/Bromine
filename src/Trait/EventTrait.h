#ifndef _TRAIT_EVENT_H_
#define _TRAIT_EVENT_H_

#include "Trait.h"
#include "../Server/EventServer.h"

namespace BromineEngine {

class EventTrait : public Trait<EventTrait, EventServer> {
friend class EventServer;
protected:
	EventTrait(const NodeID owner);

public:
	~EventTrait();
};

}

#endif //_TRAIT_EVENT_H_