#include "manager.h"
#include "agenda.h"
#include "chinese_restaurant.h"
#include "customer_group.h"
#include "logger.h"
#include "process.h"
#include "table.h"
#include "statistics.h"
using namespace std;

Manager::Manager(ChineseRestaurant* r, Agenda* a, double service_time) : Process(a),
	restaurant_(r),  
	served_group_(nullptr),
	time_of_serice(service_time),
	state_(CheckForCustomer)
{
	logger_ = Logger::GetInstance();
}

Manager::~Manager()
{
}

bool Manager::IsFree()
{
	return(served_group_ == nullptr);
}

void Manager::Execute(double current_time)
{
	switch (state_)
	{
	case CheckForCustomer:
		logger_->Print("Manager::CheckForCustomerState()", Logger::L2);
		if (!restaurant_->q_to_manager.empty())
		{
			state_ = StartOfService;
			logger_->Print("        - Manager starts service", Logger::L4);
			this->Execute(current_time);
		}
		else
		{
			logger_->Print("        - Queue to Manager is empty", Logger::L4);
		}
		break;

	case StartOfService:
			
		logger_->Print("Manager::StartOfServiceState()", Logger::L2);
		HandleStartOfServiceState(current_time);
		break;

	case EndOfService:
		logger_->Print("Manager::EndOfServiceState()", Logger::L2);
		HandleEndOfServiceState(current_time);
		break;
	}
	
}

void Manager::HandleStartOfServiceState(double current_time)
{
	served_group_ = restaurant_->q_to_manager.front();

	//checking what size of tbl is needed:
	if (served_group_->GetAmount() == 4)	//4 ppl
	{
		for (auto i = 0; i < restaurant_->tables_4_ppl.size(); i++)
		{
			if (restaurant_->tables_4_ppl[i]->IsEmpty())
			{
				restaurant_->tables_4_ppl[i]->AssignCustomers(served_group_);
				served_group_->TakeTable(restaurant_->tables_4_ppl[i]);
				logger_->Print("        - Manager takes Group " + to_string(served_group_->GetID()) + " to 4-people table nr. " + to_string(i), Logger::L4);

				ActivateAndPrintLogger(current_time);	//Activate() and Loggers
				break;
			}
		}
	}
	else if (served_group_->GetAmount() == 3)	//3 ppl
	{
		for (auto i = 0; i < restaurant_->tables_3_ppl.size(); i++)
		{
			if (restaurant_->tables_3_ppl[i]->IsEmpty())
			{
				restaurant_->tables_3_ppl[i]->AssignCustomers(served_group_);
				served_group_->TakeTable(restaurant_->tables_3_ppl[i]);
				logger_->Print("        - Manager takes Group " + to_string(served_group_->GetID()) + " to 3-people table nr. " + to_string(i), Logger::L4);

				ActivateAndPrintLogger(current_time);	//Activate() and Loggers
				break;
			}
		}
	}
	else 			//1 or 2 ppl
	{
		for (auto i = 0; i < restaurant_->tables_2_ppl.size(); i++)
		{
			if (restaurant_->tables_2_ppl[i]->IsEmpty())
			{
				restaurant_->tables_2_ppl[i]->AssignCustomers(served_group_);
				served_group_->TakeTable(restaurant_->tables_2_ppl[i]);
				logger_->Print("        - Manager takes Group " + to_string(served_group_->GetID()) + " to 2-people table nr. " + to_string(i), Logger::L4);

				ActivateAndPrintLogger(current_time);	//Activate() and Loggers
				break;
			}

			if (i == restaurant_->tables_2_ppl.size() - 1)	//lack of free tables
			{
				logger_->Print("        - No empty table for Group " + to_string(served_group_->GetID()) + "  - they wait. ", Logger::L4);
				served_group_->GoSleep();
			}
		}

	}
	
}

void Manager::HandleEndOfServiceState(double current_time)
{
	served_group_->Awake();			//wake customers
	served_group_->GoToTables();	//change state of customers
	
	state_ = CheckForCustomer;
	logger_->Print("        - Manager is ready to serve another Group", Logger::L4);
	served_group_->Activate(current_time);
	logger_->Print("    CustomerGroupGoToTableEvent at " + to_string(current_time), Logger::L3, Logger::LOG_NEW_EVENT);
	served_group_ = nullptr;
	this->Execute(current_time);
	
}

void Manager::ActivateAndPrintLogger(double &current_time)	//pass by ref
//function made to avoid writing same code 3 times
{
	state_ = EndOfService;

	served_group_->CalculateTableWaitingTime(current_time);
	//time spent in managers Q
	restaurant_->statistics->GatherTableQueueLength(current_time, served_group_->GetTableWaitingTime(), static_cast<int>(restaurant_->q_to_manager.size()));

	 //waiting time for table
	restaurant_->statistics->GatherTableWaitingTime(current_time, served_group_->GetTableWaitingTime(), served_group_->GetID());

	restaurant_->q_to_manager.pop();

	current_time += time_of_serice; // +time MT
	this->Activate(current_time);
	logger_->Print("    ManagerEndOfServiceEvent at " + to_string(current_time), Logger::L3, Logger::LOG_NEW_EVENT);
}
