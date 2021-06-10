#include "logger.h"
#include "agenda.h"
#include "process.h"
#include "waiter.h"
#include "customer_group.h"
#include "chinese_restaurant.h"
#include "table.h"
#include "manager.h"
#include "rng.h"
#include "random_generator.h"
#include "statistics.h"
using namespace std;


Waiter::Waiter(ChineseRestaurant* r, Agenda* a,int id) : Process(a),
restaurant_(r),
served_group_(nullptr),
state_(StartOfService),
terminated_(false),
kWaiterID_(id)
{
	logger_ = Logger::GetInstance();
}

Waiter::~Waiter()
{
}

bool Waiter::IsFree()
{
	return(served_group_ == nullptr);
}

void Waiter::Execute(double current_time)
{
	if (!terminated_)
	{
		switch (state_)
		{
		case StartOfService:
			
			logger_->Print("Waiter " + to_string(kWaiterID_) + "::StartOfServiceState()", Logger::L2);
			if (!restaurant_->q_to_waiters.empty())
			{
				
				served_group_ = restaurant_->q_to_waiters.front();

				served_group_->CalculateWaiterWaitingTime(current_time);	//waiting time for waiter
				restaurant_->statistics->GatherWaiterWaitingTime(current_time, served_group_->GetWaiterWaitingTime(), served_group_->GetID());

				restaurant_->q_to_waiters.pop();
				
				logger_->Print("        - Waiter "+to_string(kWaiterID_)+" starts service of Group " + to_string(served_group_->GetID()), Logger::L4);
			
				current_time += restaurant_->rng->waiter_service_time_generator->Rand();	// +time WT
				this->Activate(current_time);
				logger_->Print("    WaiterEndOfServiceEvent at " + to_string(current_time), Logger::L3, Logger::LOG_NEW_EVENT);
				
				state_ = EndOfService;
				break;
			}
			else
			{
				logger_->Print("        - Queue to Waiters is empty", Logger::L4);
			}
			break;

		case EndOfService:
			logger_->Print("Waiter " + to_string(kWaiterID_) + "::EndOfServiceState()", Logger::L2);
			
			served_group_->GoToCashiers();						//change state of customers
			served_group_->Awake();								//wake customers
			served_group_->GetTableTaken()->RemoveCustomers();	//free the table	
			
			logger_->Print("        - Waiter " + to_string(kWaiterID_) + " is ready to serve another Group", Logger::L4);
			
			restaurant_->manager->Execute(current_time);	//manager checks for customers

			served_group_->Activate(current_time);
			logger_->Print("    CustomerGroupPaymentEvent at " + to_string(current_time), Logger::L3, Logger::LOG_NEW_EVENT);

			served_group_ = nullptr;
			state_ = StartOfService;
			this->Execute(current_time);
			break;
		}
	}
}
