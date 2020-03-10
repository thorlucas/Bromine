#ifndef _TRAIT_EVENT_H_
#define _TRAIT_EVENT_H_

#include "Trait.h"
#include "../Server/EventServer.h"
#include "../Util/Events.h"

namespace BromineEngine {

class EventDelegate {
public:
	virtual void onKeyEvent(const KeyboardEvent& event) {};
	virtual void onMouseEvent() {};
};

class EventTrait : public Trait {
DECLARE_BASE_TRAIT(EventServer)
private:
	EventDelegate* delegate;

protected:
	EventTrait(const NodeID owner);

	void onKeyEvent(const KeyboardEvent& event);
	void onMouseEvent();

public:
	~EventTrait();

	void setDelegate(EventDelegate* delegate);
};

}

#endif //_TRAIT_EVENT_H_