#include "customer_group.h"
#include "agenda.h"
#include "buffet.h"
#include "cashier.h"
#include "chinese_restaurant.h"
#include "logger.h"
#include "manager.h"
#include "process.h"
#include "table.h"
#include "waiter.h"
#include "rng.h"
#include "random_generator.h"
#include "statistics.h"
using namespace std;

int CustomerGroup::global_id_ = 0;

CustomerGroup::CustomerGroup(ChineseRestaurant* r, int amount, Agenda* a) : Process(a),
	kNumID_(global_id_++),
	restaurant_(r),
	terminated_(false),
	state_(New),
	table_taken_(nullptr),
	cashier_taken_(nullptr),
	kNumOfPeople_(amount)
{
	logger_ = Logger::GetInstance();
	waiting_time_for_table = 0;
	waiting_time_for_waiter = 0;
	time_in_cashier_q = 0;
}


CustomerGroup::~CustomerGroup()
{
}

int CustomerGroup::GetID() const
{
	return kNumID_;
}

int CustomerGroup::GetAmount() const
{
	return kNumOfPeople_;
}

void CustomerGroup::Awake()
{
	active_ = true;
}

void CustomerGroup::GoSleep()
{
	active_ = false;
}

void CustomerGroup::GoToTables()
{
	state_ = StartOfTables;
}

void CustomerGroup::GoToCashiers()
{
	state_ = GoToPay;
}

bool CustomerGroup::IsTerminated()
{
	return terminated_;
}

void CustomerGroup::TakeTable(Table* tbl)
{
	table_taken_ = tbl;
}

Table* CustomerGroup::GetTableTaken()
{
	return table_taken_;
}

void CustomerGroup::TakeCashier(Cashier* cshr)
{
	cashier_taken_ = cshr;
}

Cashier* CustomerGroup::GetCashierTaken()
{
	return cashier_taken_;
}

void CustomerGroup::CalculateTableWaitingTime(double current_time)
{
	waiting_time_for_table = current_time - waiting_time_for_table;
}

double CustomerGroup::GetTableWaitingTime()
{
	return waiting_time_for_table;
}

void CustomerGroup::CalculateWaiterWaitingTime(double current_time)
{
	waiting_time_for_waiter =  current_time - waiting_time_for_waiter;
}

double CustomerGroup::GetWaiterWaitingTime()
{
	return waiting_time_for_waiter;
}



void CustomerGroup::Execute(double current_time)
{
	this->active_ = true;

	while (active_)
	{
		switch (state_)
		{
		case New:
			
			logger_->Print("CustomerGroup " + to_string(kNumID_) + "::NewCustomerState()", Logger::L2);
			HandleNewState(current_time);
			break;

		case StartOfTables:
			logger_->Print("CustomerGroup " + to_string(kNumID_) + "::StartOfTablesState()", Logger::L2);
			HandleStartOfTablesState(current_time);
			break;

		case StartOfBuffet:
			logger_->Print("CustomerGroup " + to_string(kNumID_) +"::StartOfBuffetState()", Logger::L2);
			HandleStartOfBuffetState(current_time);
			break;

		case GoToPay:
			logger_->Print("CustomerGroup " + to_string(kNumID_) +"::GoToPayState()", Logger::L2);
			HandleGoToPayState(current_time);
			break;

		case EndOfService:
			logger_->Print("CustomerGroup " + to_string(kNumID_) +"::EndOfServiceState()", Logger::L2);
			HandleEndOfServiceState(current_time);
			break;
		}
	}
}



void CustomerGroup::HandleNewState(double current_time)
{
	logger_->Print("        - Group " + to_string(kNumID_) + ", having " +to_string(kNumOfPeople_) + " people arrives restaurant", Logger::L4);

	int going_to_tables = static_cast<int> (restaurant_->rng->probability_tables_buffet_generator->Rand(0,100)) % 2;
	
	auto* new_group = new CustomerGroup(restaurant_, restaurant_->SetNumberOfPeople(),agenda_);
	
	double next_group_arrival_time = current_time + restaurant_->rng->new_customer_arrival_time_generator->Rand();

	new_group->Activate(next_group_arrival_time);
	logger_->Print("    NewCustomerGroupEvent at " + to_string(next_group_arrival_time),
		Logger::L3, Logger::LOG_NEW_EVENT);

	active_ = false;
	if (going_to_tables)		//customers go to tables
	{
		restaurant_->q_to_manager.push(this);
		waiting_time_for_table = current_time;
		logger_->Print("        - Group " + to_string(kNumID_) + " goes to Manager", Logger::L4);
		
		if (restaurant_->manager->IsFree())
		{
			restaurant_->manager->Execute(current_time);
		}
		else
		{
			logger_->Print("        - Group " + to_string(kNumID_) + " waits in a queue to Manager while he is busy", Logger::L4);
		}
	}	
	else						//customers go to buffet
	{
		restaurant_->q_to_buffet.push(this);
		logger_->Print("        - Group " + to_string(kNumID_) + " goes to Buffet", Logger::L4);
		if (restaurant_->buffet->IsFreeEnough(this->GetAmount()))
		{
			state_ = StartOfBuffet;
			
			logger_->Print("        - Group " + to_string(kNumID_) + " starts eating at Buffet", Logger::L4);
			this->Execute(current_time);
		}
		else
		{
			logger_->Print("        - Group " + to_string(kNumID_) + " waits in a queue to Buffet (not enough space)", Logger::L4);
		}

	}
}
void CustomerGroup::HandleStartOfTablesState(double current_time)
{
	logger_->Print("        - Group " + to_string(kNumID_) + " is seated at the table", Logger::L4);
	active_ = false;
	restaurant_->q_to_waiters.push(this);
	waiting_time_for_waiter = current_time;
	
	for (auto i = 0; i < restaurant_->waiters.size(); i++)		//check for waiter
	{
		if (restaurant_->waiters[i]->IsFree())
		{
			restaurant_->waiters[i]->Execute(current_time);
			break;
		}
		else if (i == restaurant_->waiters.size())
		{
			logger_->Print("        - Group " + to_string(kNumID_) + " has to wait for Waiter", Logger::L4);
		}
	}
	
}
void CustomerGroup::HandleStartOfBuffetState(double current_time)
{
	logger_->Print("        - Group " + to_string(kNumID_) + " starts eating at Buffet", Logger::L4);
	restaurant_->q_to_buffet.pop();
	restaurant_->buffet->TakeSeats(this->GetAmount());			//take places in buffet
	current_time += restaurant_->rng->buffet_eating_time_generator->Rand();	//wait time BT		
	this->Activate(current_time);
	
	logger_->Print("    CustomerGroupPaymentEvent at " + to_string(current_time), Logger::L3, Logger::LOG_NEW_EVENT);
	restaurant_->buffet->FreeSeats(this->GetAmount());
	active_ = false;
	state_ = GoToPay;
	
	
}
void CustomerGroup::HandleGoToPayState(double current_time)
{
	queue<CustomerGroup*> temp_q = restaurant_->q_to_cashiers;
	bool already_in_q = false;
	while (!temp_q.empty())							//check if group is already in Q
	{
		if (temp_q.front()->GetID() == kNumID_)
		{
			already_in_q = true;
			break;
		}
		temp_q.pop();
	}
	if (!already_in_q)
	{
		restaurant_->q_to_cashiers.push(this);
		time_in_cashier_q = current_time;
	}
	



	for (int i = 0; i < restaurant_->cashiers.size(); i++)		//check for cashier
	{
		if (restaurant_->cashiers[i]->IsFree())
		{
			
			time_in_cashier_q = current_time - time_in_cashier_q;
			restaurant_->statistics->GatherCashiersQueueLength(current_time,time_in_cashier_q,static_cast<int>(restaurant_->q_to_cashiers.size()));
			restaurant_->q_to_cashiers.pop();

			logger_->Print("        - Group " + to_string(kNumID_) + " is served by Cashier "+ to_string(i), Logger::L4);
			restaurant_->cashiers[i]->AssignCustomers(this);
			cashier_taken_ = restaurant_->cashiers[i];
			current_time += restaurant_->rng->cashier_service_time_generator->Rand();	//wait CT
			this->Activate(current_time);
			logger_->Print("    CustomerGroupEndOfServiceEvent at " + to_string(current_time), Logger::L3, Logger::LOG_NEW_EVENT);

			
			active_ = false;
			state_ = EndOfService;
			break;
		}
		else if (i == restaurant_->cashiers.size()-1)
		{
			logger_->Print("        - Group " + to_string(kNumID_) + " has to wait for Cashier", Logger::L4);
			active_ = false;
		}
		
	}
	
}
void CustomerGroup::HandleEndOfServiceState(double current_time)
{
	terminated_ = true;
	active_ = false;
	logger_->Print("        - Group " + to_string(kNumID_) + " finished service and is terminated", Logger::L4);

	
	cashier_taken_->RemoveCustomers();
	if (!restaurant_->q_to_cashiers.empty())
	{
		
		restaurant_->q_to_cashiers.front()->Activate(current_time);
		restaurant_->q_to_cashiers.front()->Awake();
		logger_->Print("    CustomerGroupPaymentEvent at " + to_string(current_time), Logger::L3, Logger::LOG_NEW_EVENT);
	}

	
}
