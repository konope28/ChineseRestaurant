// ReSharper disable All
#include <cstdlib>
#include <iostream>
#include "simulator.h"
#include "agenda.h"
#include "process.h"
#include "chinese_restaurant.h"
#include "customer_group.h"
#include "manager.h"
#include "waiter.h"
#include "rng.h"
#include "statistics.h"
#include "kernels.h"
using namespace std;

Simulator::Simulator(double stop_time, double mng_serv_time, int nr_of_tbl2, int nr_of_tbl3, int nr_of_tbl4, int nr_of_wtrs, int nr_of_cshrs, int nr_of_buff_sts) :
	kStopTime_(stop_time),
	kMngServTime_(mng_serv_time),
	kNumOfTables2_(nr_of_tbl2),
	kNumOfTables3_(nr_of_tbl3),
	kNumOfTables4_(nr_of_tbl4),
	kNumOfWaiters_(nr_of_wtrs),
	kNumOfCashiers_(nr_of_cshrs),
	kNumOfBuffetSeats_(nr_of_buff_sts)
{
	agenda_ = nullptr;
	restaurant_ = nullptr;
	rng_ = nullptr;
	statistics_ = nullptr;
}

Simulator::~Simulator()
{
	delete restaurant_;
	delete agenda_;
	delete rng_;
	delete statistics_;
}

void Simulator::Initialize(string kernels_file_path, int sim_set_idx, double start_time, bool step_by_step, Logger::LogVerbosity verb, double lambda_wtrs, double lambda_cshrs, double mean_arrivals, double stddev_arrivals, double mean_buffet, double stddev_buffet)
{
	Kernels *kernels = new Kernels();
	kernels->ReadKernels(kernels_file_path);
	
	rng_ = new RNG();
	rng_->Initialize(kernels, sim_set_idx, lambda_wtrs, lambda_cshrs, mean_arrivals, stddev_arrivals, mean_buffet, stddev_buffet);
	
	statistics_ = new Statistics(start_time, kStopTime_);
	statistics_->Initialize();
	
	agenda_ = new Agenda();
	
	restaurant_ = new ChineseRestaurant(kMngServTime_, kNumOfTables2_, kNumOfTables3_, kNumOfTables4_, kNumOfWaiters_, kNumOfCashiers_, kNumOfBuffetSeats_, agenda_, rng_, statistics_);
	
	current_time_ = 0;
	step_by_step_ = step_by_step;
	Logger::GetInstance()->SetLogVerbosity(static_cast<Logger::LogVerbosity>(verb));
}

void Simulator::Start()
{
	Process* process;

	(new CustomerGroup(restaurant_, restaurant_->SetNumberOfPeople(), agenda_))->Activate(current_time_);

	while (current_time_ <= kStopTime_)
	{
		
		auto event = agenda_->RemoveEvent();
		current_time_ = event->event_time;

		Logger::GetInstance()->Print	(("\n------------------------------------------------------------------------\n"), Logger::L1);
		Logger::GetInstance()->Print(("CLOCK = " + to_string(current_time_) + "\n"), Logger::L1);

		


		process = event->process;
		process->Execute(current_time_);

		delete event;

		if (process->IsTerminated())
		{
			delete process;
		}

		if (step_by_step_)
		{
			printf("Press ENTER to continue...");
			string l; getline(cin, l);
		}
		
	}
	statistics_->DisplayResults();	//display statistical data
}