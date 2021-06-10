#include "agenda.h"
#include "time_event.h"


Agenda::Agenda()
{
}

Agenda::~Agenda()
{
	for (auto val : timeline_)
		delete val;
}
void Agenda::AddEvent(TimeEvent* t_ev)
{
	timeline_.insert(t_ev);
}

TimeEvent* Agenda::RemoveEvent()
{
	assert(!timeline_.empty() && "Agenda::RemoveEvent()::No more events to simulate!");
	TimeEvent* res = *timeline_.begin();
	timeline_.erase(res);
	return res;
}

double Agenda::GetFirstEventTime()
{
	assert(!timeline_.empty() && "Agenda::FirstEventTime(): No more events to simulate!");
	return(*timeline_.begin())->event_time;
}
