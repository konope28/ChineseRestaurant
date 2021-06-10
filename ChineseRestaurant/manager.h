#ifndef MODEL_MANAGER_H_
#define MODEL_MANAGER_H_
#include "process.h"

class CustomerGroup;
class Agenda;
class Logger;
struct ChineseRestaurant;

class Manager : public Process
{
public:
	Manager(ChineseRestaurant* r,Agenda* a, double service_time);
	~Manager();
	bool IsFree();
	void Execute(double current_time);
	bool IsTerminated() { return false; };

private:
	enum State
	{
		CheckForCustomer,
		StartOfService,
		EndOfService
	};

	void HandleStartOfServiceState(double current_time);
	void HandleEndOfServiceState(double current_time);
	void ActivateAndPrintLogger(double &current_time);

	State state_;
	CustomerGroup* served_group_;
	ChineseRestaurant* restaurant_;
	Logger* logger_;
	double time_of_serice;
};

#endif /*MODEL_MANAGER_H_*/
