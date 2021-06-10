#include "time_event.h"


TimeEvent::TimeEvent(double in_event_time, Process* p) :
	event_time(in_event_time), 
	process(p)
{
}

TimeEvent::~TimeEvent()
{
}

bool TimeEventComparator::operator()(const TimeEvent* a, const TimeEvent* b) const
{
	return a->event_time < b->event_time;
}
