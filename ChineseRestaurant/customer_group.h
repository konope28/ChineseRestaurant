#ifndef MODEL_CUSTOMER_GROUP_H_
#define MODEL_CUSTOMER_GROUP_H_
#include "process.h"
#include <iostream>

class Agenda;
class Logger;
class Table;
class Cashier;
struct ChineseRestaurant;


class CustomerGroup : public Process
{
public:
	CustomerGroup(ChineseRestaurant* r,int amount, Agenda* a);
	~CustomerGroup();

	int GetID() const;
	int GetAmount() const;
	void Awake();
	void GoSleep();
	void GoToTables();
	void GoToCashiers();
	bool IsTerminated();

	void TakeTable(Table* tbl);
	Table* GetTableTaken();
	void TakeCashier(Cashier* cshr);
	Cashier* GetCashierTaken();

	void CalculateTableWaitingTime(double current_time);
	double GetTableWaitingTime();
	void CalculateWaiterWaitingTime(double current_time);
	double GetWaiterWaitingTime();

	void Execute(double current_time);

private:
	enum State 
	{
		New,
		StartOfTables,
		StartOfBuffet,
		GoToPay,
		EndOfService
	};

	void HandleNewState(double current_time);
	void HandleStartOfTablesState(double current_time);
	void HandleStartOfBuffetState(double current_time);
	void HandleGoToPayState(double current_time);
	void HandleEndOfServiceState(double current_time);

	static int global_id_;
	const int kNumID_;
	const int kNumOfPeople_;

	State state_;
	ChineseRestaurant* restaurant_;
	Logger* logger_;
	Table* table_taken_;
	Cashier* cashier_taken_;
	bool terminated_;
	bool active_;

	double waiting_time_for_table;
	double waiting_time_for_waiter;
	double time_in_cashier_q;
};

#endif /*MODEL_CUSTOMERGROUP_H_*/