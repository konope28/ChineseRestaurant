#ifndef SIMULATOR_TIME_EVENT_H_
#define SIMULATOR_TIME_EVENT_H_

class Process;
class CustomerGroup;

struct TimeEvent
{
	TimeEvent(double in_event_time, Process* p);
	virtual ~TimeEvent();

	double event_time;
	Process* process;
};

struct TimeEventComparator
{
public:
	bool operator()(const TimeEvent* a, const TimeEvent* b) const;
};

#endif /*SIMULATOR_TIME_EVENT_H_*/
