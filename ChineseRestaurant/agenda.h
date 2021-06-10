#ifndef SIMULATOR_AGENDA_H_
#define SIMULATOR_AGENDA_H_
#include "time_event.h"
#include <set>
#include <cassert>
#include <set>

class Agenda
{
public:
	Agenda();
	~Agenda();
	void AddEvent(TimeEvent* t_ev);
	TimeEvent* RemoveEvent();
	double GetFirstEventTime();

private:
	std::multiset <TimeEvent*, TimeEventComparator> timeline_;
};

#endif /*SIMULATOR_AGENDA_H_*/
