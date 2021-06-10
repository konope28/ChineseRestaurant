#ifndef MODEL_CHINESE_RESTAURANT_H_
#define MODEL_CHINESE_RESTAURANT_H_
#include <queue>
#include <iostream>

class CustomerGroup;
class Manager;
class Table;
class Agenda;
class Waiter;
class Cashier;
class Buffet;
class Statistics;
struct RNG;

struct ChineseRestaurant
{
	ChineseRestaurant(double mng_serv_time, int nr_of_tbl2, int nr_of_tbl3, int nr_of_tbl4, int nr_of_wtrs, int nr_of_cshrs, int nr_of_buff_sts, Agenda* agenda, RNG* rng, Statistics* statistics);
	~ChineseRestaurant();
	int SetNumberOfPeople();

	std::queue<CustomerGroup*> q_to_manager;
	std::queue<CustomerGroup*> q_to_buffet;
	std::queue<CustomerGroup*> q_to_cashiers;
	std::queue<CustomerGroup*> q_to_waiters;

	std::vector<Table*> tables_2_ppl;
	std::vector<Table*> tables_3_ppl;
	std::vector<Table*> tables_4_ppl;
	std::vector<Waiter*> waiters;
	std::vector<Cashier*> cashiers;

	Manager* manager;
	Buffet* buffet;
	Agenda* agenda;
	RNG* rng;
	Statistics* statistics;

	const double kMngServTime;
	const int kNumOfTables2;
	const int kNumOfTables3;
	const int kNumOfTables4;
	const int kNumOfWaiters;
	const int kNumOfCashiers;
	const int kNumOfBuffetSeats;
};

#endif /*MODEL_CHINESE_RESTAURANT_H_*/
