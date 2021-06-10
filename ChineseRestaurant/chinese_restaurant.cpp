#include "process.h"
#include "chinese_restaurant.h"
#include "customer_group.h"
#include "manager.h"
#include "table.h"
#include "waiter.h"
#include "cashier.h"
#include "buffet.h"
#include "simulator.h"
#include "rng.h"
#include "random_generator.h"
#include "statistics.h"


ChineseRestaurant::ChineseRestaurant(double mng_serv_time, int nr_of_tbl2, int nr_of_tbl3, int nr_of_tbl4, int nr_of_wtrs, int nr_of_cshrs, int nr_of_buff_sts, Agenda* agenda, RNG* rng, Statistics* statistics): 
	kMngServTime(mng_serv_time),
	kNumOfTables2(nr_of_tbl2), 
	kNumOfTables3(nr_of_tbl3), 
	kNumOfTables4(nr_of_tbl4),
	kNumOfWaiters(nr_of_wtrs),
	kNumOfCashiers(nr_of_cshrs), 
	kNumOfBuffetSeats(nr_of_buff_sts),
	agenda(agenda),
	rng(rng),
	statistics(statistics)
{
	for (int i = 0; i < kNumOfTables2; i++)				//vector of 2 ppl tables
	{
		tables_2_ppl.push_back(new Table(2));
	}
	for (int i = 0; i < kNumOfTables3; i++)				//vector of 3 ppl tables
	{
		tables_3_ppl.push_back(new Table(3));
	}
	for (int i = 0; i < kNumOfTables4; i++)				//vector of 4 ppl tables
	{
		tables_4_ppl.push_back(new Table(4));
	}
	for (int i = 0; i < kNumOfWaiters; i++)				//vector of waiters
	{
		waiters.push_back(new Waiter(this,agenda,i));
	}
	for (int i = 0; i < kNumOfCashiers; i++)			//vector of cashiers
	{
		cashiers.push_back(new Cashier);
	}
	manager = new Manager(this, agenda, kMngServTime);	//manager
	buffet = new Buffet(kNumOfBuffetSeats);				//buffet
}
ChineseRestaurant::~ChineseRestaurant()
{																			
	while (!q_to_manager.empty())				//deleting customers from manager q
	{
		CustomerGroup* c = q_to_manager.front();
		q_to_manager.pop();
		delete c;
	}
	while (!q_to_buffet.empty())				//deleting customers from buffet q
	{
		CustomerGroup* c = q_to_buffet.front();
		q_to_buffet.pop();
		delete c;
	}
	while (!q_to_cashiers.empty())				//deleting customers from cashiers q
	{
		CustomerGroup* c = q_to_cashiers.front();
		q_to_cashiers.pop();
		delete c;
	}
	for (auto* tbl2 : tables_2_ppl)			//deleting 2 ppl tables
	{
		delete tbl2;
	}
	for (auto* tbl3 : tables_3_ppl)			//deleting 3 ppl tables
	{
		delete tbl3;
	}
	for (auto* tbl4 : tables_4_ppl)			//deleting 4 ppl tables
	{
		delete tbl4;
	}
	for (auto* wt : waiters)				//deleting waiters
	{
		delete wt;
	}
	for (auto* cs : cashiers)				//deleting cachiers
	{
		delete cs;
	}
	delete manager;							//deleting manager;
	delete buffet;							//deleting buffet
}

int ChineseRestaurant::SetNumberOfPeople()
{
	double random = rng->probability_amount_of_customer_group_generator->Rand(1, 100);
	if (random > 11 && random <= 44) 
		return 2;

	else if (random > 44 && random <= 77)
		return 3;

	else if (random > 77)
		return 4;

	else return 1;
}