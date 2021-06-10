#ifndef MODEL_PROCESS_H_
#define MODEL_PROCESS_H_
#include <iostream>
class Agenda;

class Process
{
	
public:
	Process(Agenda *a);
	virtual ~Process();
	void Activate(double event_time);
	virtual void Execute(double time);
	virtual bool IsTerminated()=0;

	Agenda* agenda_;
};

#endif /*MODEL_PROCESS_H_*/

