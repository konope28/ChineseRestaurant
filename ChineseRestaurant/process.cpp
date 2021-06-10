#include "process.h"
#include "agenda.h"

using namespace std;

Process::Process(Agenda *a): agenda_(a)
{
}

Process::~Process()
{
}

void Process::Execute(double time) 
{
}

void Process::Activate(double event_time)
{
	agenda_->AddEvent(new TimeEvent(event_time, this));
}
